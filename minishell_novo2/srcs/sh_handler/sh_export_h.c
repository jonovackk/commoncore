/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:49 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:05:50 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Validates the syntax of the export string
 * 
 * What it does:
 * - Checks if the string is a valid format for export variables in a shell.
 * - Validates that the string doesn't start with a digit or is empty.
 * - Allows only alphanumeric characters or underscores before the equal sign.
 * - Supports an optional `+=` syntax for appending values.
 * 
 * @param str The string to be validated.
 * @return 1 if the syntax is valid, 0 otherwise.
 */
int     sh_export_syntax(char *str)
{
    char    *tmp = str;
    
    // Check if the string starts with a digit or is empty (invalid cases)
    if (ft_isdigit(*str) || !*str)
        return (0);

    // Validate characters before the equal sign (must be alphanumeric or '_')
    while (*str && (ft_isalnum(*str) || *str == '_') && *str != '=')
        str++;

    // Allow "key+=" syntax for appending values
    if (*str == '+' && *(str + 1) == '=')
        return (1);

    // Valid if there is a single '=' or if the string ends after valid characters
    return ((tmp != str && *str == '=') || !*str);
}

/**
 * @brief Displays the sorted list of exported environment variables
 * 
 * What it does:
 * - Retrieves the list of environment variables from the shell's environment.
 * - Sorts the variables alphabetically.
 * - Outputs each variable in the format `declare -x VAR=value`, excluding the `_=` variable.
 * 
 * @param cmd The command structure containing the environment and output file descriptor.
 * @return ERR_NONE if the export list is displayed successfully, ERR_FAIL otherwise.
 */
int     sh_display_expor_var(t_sh_cmd *cmd)
{
    char        **env_array;
    char        **tmp;
    char        *line;

    // Retrieve the environment variables as strings
    env_array = sh_create_env_array(*(cmd->environment), 1);
    if (!env_array)
        return (ERR_FAIL_GENERAL); // Return failure if unable to get the environment variables

    // Sort the environment variables alphabetically
    ft_sort_strs_tab(env_array, ft_tab_len(env_array));

    tmp = env_array;
    while (*tmp)
    {
        // Skip the variable that is named "_="
        if (ft_strncmp(*tmp, "_=", 2))
        {
            // Format each variable in the `declare -x` format
            line = ft_strjoin("declare -x ", *tmp, NULL, 0);
            ft_dprintf(cmd->output_fd, "%s\n", line); // Output the variable to the file
            free(line); // Free the memory allocated for the formatted line
        }
        tmp++;
    }

    // Free the environment array after use
    ft_free_tab((void **)env_array);
    return (ERR_NONE); // Return success after displaying the export list
}


/**
 * @brief Adds or updates an environment variable in the shell's environment
 * 
 * What it does:
 * - If the input string contains an `=`, splits the string into the variable name and value.
 * - Trims any quotes from the value.
 * - If the variable name ends with `+`, the function extends the environment variable.
 * - Otherwise, it updates or adds the environment variable.
 * - If the input string does not contain an `=`, the function adds the variable with a NULL value.
 * 
 * @param cmd The command structure containing the environment.
 * @param tmp The string containing the environment variable to add or update.
 * @return ERR_NONE if the operation is successful.
 */
int     sh_update_env_var(t_sh_cmd *cmd, char *tmp)
{
    char        **var = NULL;
    char        *trimmed;

    // If the input contains '=', it indicates a variable assignment
    if (ft_strchr(tmp, '='))
    {
        // Split the input into name and value based on the '=' symbol
        ft_strapp(&var, ft_strndup(tmp, ft_strcspn(tmp, "=")));
        ft_strapp(&var, ft_strdup(tmp + ft_strlen(*var) + 1));

        // Trim any quotes from the value
        trimmed = ft_strtrim(var[1], "\"");
        free(var[1]);
        var[1] = trimmed;

        // If the variable name ends with '+', extend the environment variable
        if (ft_strlen(var[0]) && var[0][ft_strlen(var[0]) - 1] == '+')
            sh_extend_env(cmd->environment, var[0], ft_strdup(var[1]));
        else
        {
            // Update the environment variable, or set it to an empty string if the value is NULL
            if (var[1])
                sh_update_env(cmd->environment, var[0], ft_strdup(var[1]));
            else
                sh_update_env(cmd->environment, var[0], "");
        }

        // Free the memory allocated for the variable name and value
        ft_free_tab((void **)var);
    }
    else if (!sh_find_env(*(cmd->environment), tmp))
    {
        // If the input doesn't contain '=', add the variable with NULL value
        sh_update_env(cmd->environment, tmp, NULL);
    }
    
    return (ERR_NONE); // Return success after the operation
}

/**
 * @brief Handles the export of environment variables in the shell
 * 
 * What it does:
 * - If there is only one argument and it’s a request to show the list of exported variables, it displays the list.
 * - Otherwise, it processes each argument to export environment variables.
 * - It validates the syntax of each argument, exports or updates the variables, and handles any errors.
 * 
 * @param cmd The command structure containing the arguments and environment.
 * @return ERR_NONE if the export operation is successful, ERR_FAIL if an error occurs.
 */
int    sh_execute_export(t_sh_cmd *cmd)
{
    char        **tmp;
    error_t     errcode;

    tmp = cmd->arguments;
    errcode = ERR_NONE;

    // If there's only one argument and it's to show the list, display the export list
    if (ft_tab_len(tmp) == 1 && sh_display_expor_var(cmd)) // possivel erro verificar
        errcode = ERR_FAIL_GENERAL;
    else
    {
        // Process each argument and attempt to export them
        while (*(++tmp))
        {
            // Validate the syntax of the export variable
            if (!sh_export_syntax(*tmp))
            {
                // Print error message if the syntax is invalid
                sh_display_error(ERR_INVALID, *tmp);
                errcode = ERR_FAIL_GENERAL;
            }
            // Export or update the variable in the environment
            if (sh_update_env_var(cmd, *tmp))
                errcode = ERR_FAIL_GENERAL;
        }
    }

    // Update the environment context
    sh_env_context(cmd->environment);

    // Return the error code, either success or failure
    return (errcode);
}
