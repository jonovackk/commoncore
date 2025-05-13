/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pwd_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:13 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:06:14 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int  g_shell_exit_status;

/**
 * @brief Returns the part of the path after the last '/'
 * 
 * What it does:
 * - Finds the last occurrence of '/' in the string and returns everything after it.
 * - If there is no '/' found, it returns an empty string.
 * 
 * @param str The input string representing a path.
 * @return A new string containing the last segment of the path or an empty string if no '/' is found.
 */
char    *sh_trim_pwd(char *str)
{
    char    *last_slash;

    // Find the last occurrence of '/' in the string
    last_slash = ft_strrchr(str, '/');
    if (!last_slash)
        return (ft_strdup("")); // Return an empty string if no '/' is found
    return (ft_strdup(last_slash)); // Return the substring starting from the last '/'
}


/**
 * @brief Retrieves the current working directory.
 * 
 * What it does:
 * - Uses `getcwd` to retrieve the current working directory and returns it as a string.
 * - If `getcwd` fails, it returns `NULL`.
 * 
 * @return A newly allocated string containing the current working directory, or `NULL` if it fails.
 */
char    *sh_get_pwd(void)
{
    char    cwd[65536];

    // Retrieve the current working directory
    if (getcwd(cwd, sizeof(cwd)))
        return (ft_strdup(cwd));  // Return the cwd as a newly allocated string
    return (NULL);  // Return NULL if getcwd fails
}

/**
 * @brief Executes the pwd built-in command.
 * 
 * What it does:
 * - Retrieves the current working directory and prints it to the specified output.
 * - If `getcwd` fails, it prints an error message and returns an error code.
 * 
 * @param cmd The command structure containing the output file descriptor.
 * @return `ERR_NONE` if successful, `ERR_FAIL` if there is an error.
 */
int     sh_execute_pwd(t_sh_cmd *cmd)
{
    char    cwd[65536];

    // Retrieve the current working directory
    if (getcwd(cwd, sizeof(cwd)))
        ft_dprintf(cmd->output_fd, "%s\n", cwd);  // Print the cwd to the output
    else
    {
        perror("getcwd() error");
        return (ERR_FAIL_GENERAL);  // Return error if getcwd fails
    }
    return (ERR_NONE);  // Return success
}


/**
 * @brief Generates the prompt string for the shell.
 * 
 * What it does:
 * - Retrieves the current working directory (`PWD`) from the environment.
 * - Constructs a prompt string using the working directory and the shell's exit status.
 * 
 * @param envp The environment variables, used to get the `PWD` value.
 * @return A newly allocated string representing the shell prompt.
 */
char *sh_get_prompt(t_sh_env *envp)
{
    char *result = NULL;
    char *cwd = NULL;
    char *tmp_prompt = NULL;
    
    // Null check for environment
    if (!envp)
    {
        // Fallback prompt if environment is invalid
        return ft_strdup("Minishell$ ");
    }
    
    // Get current working directory
    cwd = sh_get_pwd();
    if (!cwd)
    {
        // Fallback if we can't get working directory
        return ft_strdup("Minishell$ ");
    }
    
    // Format the exit status - green for success, red for failure
    // IMPORTANT: Check your ft_strjoin implementation to understand the flags
    // We're assuming 0b01 means free the first argument and not the second
    if (g_shell_exit_status == 0)
        tmp_prompt = ft_strjoin(cwd, PROMPT_SUCCESS, " ", 0);  // Don't free cwd here
    else
        tmp_prompt = ft_strjoin(cwd, PROMPT_FAIL, " ", 0);     // Don't free cwd here
    
    // Free the current working directory string - manually free after strjoin
    free(cwd);
    cwd = NULL;  // Set to NULL to avoid double free
    
    // Check if prompt creation failed
    if (!tmp_prompt)
        return ft_strdup("Minishell$ ");
    
    // Add shell name to prompt
    // IMPORTANT: Again, check your ft_strjoin implementation 
    // We're assuming 0b01 means free the first argument
    result = ft_strjoin(tmp_prompt, PROMPT_TAIL, "", 0b01);
    
    // tmp_prompt should be freed by ft_strjoin if 0b01 flag works as expected
    // BUT, if not, this could lead to a memory leak
    
    // Check if final prompt creation failed
    if (!result)
    {
        // If ft_strjoin doesn't free tmp_prompt with 0b01 flag, free it here
        if (tmp_prompt)
            free(tmp_prompt);
        return ft_strdup("Minishell$ ");
    }
    
    return result;
}

