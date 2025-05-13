/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:23 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:05:27 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Loads the environment variables related to the current directory.
 * 
 * What it does:
 * - Finds and loads the "HOME", "OLDPWD", and "PWD" environment variables.
 * - Stores them in the `dir_vars` array for further use.
 * 
 * @param envp The environment structure containing the environment variables.
 * @param dir_vars An array where the directory-related environment variables will be stored.
 */
void    sh_dir_vars(t_sh_env *envp, t_sh_env **dir_vars)
{
    // Find the "HOME" environment variable and store it in the first position of dir_vars
    dir_vars[0] = sh_find_env(envp, "HOME");

    // Find the "OLDPWD" environment variable and store it in the second position of dir_vars
    dir_vars[1] = sh_find_env(envp, "OLDPWD");

    // Find the "PWD" environment variable and store it in the third position of dir_vars
    dir_vars[2] = sh_find_env(envp, "PWD");

    // Mark the end of the directory-related environment variables with a NULL pointer
    dir_vars[3] = NULL;
}

/**
 * @brief Changes the current working directory to the target path
 * 
 * What it does:
 * - If the target directory is valid, changes the current directory.
 * - If an error occurs, prints an appropriate error message based on the error.
 * 
 * @param target The path to the target directory.
 * @return ERR_NONE if the directory change is successful, ERR_FAIL otherwise.
 */
error_t sh_change_directory(char *target)
{
    // Check if the target directory is NULL or empty
    if (!target)
        return (ERR_FAIL_GENERAL);

    // Attempt to change the directory
    if (chdir(target) == -1)
    {
        // If the error is related to permission (EACCES), print the "No Permission" message
        if (errno == EACCES)
            sh_display_error(ERR_NO_PERMISS, target);
        // Otherwise, print "No such file or directory" message
        else
            sh_display_error(ERR_NO_ENTRY, target);
        
        return (ERR_FAIL_GENERAL); // Return failure if the directory change fails
    }

    return (ERR_NONE); // Return success if the directory change is successful
}


/**
 * @brief Processes the arguments for the `cd` command and determines the target directory.
 * 
 * What it does:
 * - Determines the target directory based on the number and type of arguments.
 * - Handles cases for `~` (HOME), `-` (OLDPWD), and a specified directory.
 * - Calls the `change_directory` function to perform the actual directory change.
 * 
 * @param argc The number of arguments passed to the `cd` command.
 * @param argv The arguments passed to the `cd` command.
 * @param vars The environment variables (HOME and OLDPWD).
 * @param out The file descriptor to output the result (for printing the OLD-PWD).
 * @return ERR_NONE if the directory change was successful, ERR_FAIL otherwise.
 */
error_t sh_cd_target(int argc, char **argv, t_sh_env **vars, int out)
{
    char *target = NULL;

    // Case 1: No arguments provided, use the HOME directory
    if (!argc)
        target = *(vars[0]->values);

    // Case 2: One argument provided
    else if (argc == 1)
    {
        // If argument is "~", change to HOME directory
        if (!ft_strncmp(argv[0], "~", 2) && vars[0])
            target = *(vars[0]->values);
        
        // If argument is "-", change to OLDPWD and print the old directory
        else if (!ft_strncmp(argv[0], "-", 2) && vars[1])
        {
            if (vars[1]->values)
            {
                // Print the OLD-PWD directory before changing
                ft_dprintf(out, "\033[37;1m-> %s\033[0m\n", *(vars[1]->values));
                target = *(vars[1]->values);
            }
            else
                // Print an error if OLDPWD is not set
                sh_display_error(ERR_VAR_UNSET, "OLDPWD");
        }
        // If it's any other directory, use the argument as the target
        else
            target = argv[0];
    }

    // Attempt to change to the determined target directory
    return (sh_change_directory(target));
}


/**
 * @brief Executes the built-in `cd` command to change the current directory.
 * 
 * What it does:
 * - Processes arguments passed to `cd`, determines the target directory, and attempts to change to it.
 * - Updates the `PWD` and `OLDPWD` environment variables accordingly.
 * - Prints appropriate error messages if something goes wrong (e.g., invalid arguments, unset environment variables).
 * 
 * @param cmd The command structure that contains arguments and environment variables for `cd`.
 * @return ERR_NONE if successful, ERR_FAIL if there are errors.
 */
int sh_execute_cd(t_sh_cmd *cmd)
{
    int         argc;
    char        *newdir;
    t_sh_env    *vars[4];

    argc = ft_tab_len(cmd->arguments);

    // Check if there are too many arguments for the 'cd' command
    if (argc > 2)
        sh_display_error(ERR_TOO_MANY_ARGS, "cd");

    // Load the environment variables related to directories (HOME, OLDPWD, PWD)
    sh_dir_vars(*(cmd->environment), (t_sh_env **) &vars);

    // If no argument is given and HOME is unset, print an error
    if ((argc - 1) && !vars[0])
        sh_display_error(ERR_VAR_UNSET, "HOME");

    // Process the directory argument and change the directory
    else if (sh_cd_target(argc - 1, cmd->arguments + 1, vars, cmd->output_fd))
        return (ERR_FAIL_GENERAL);

    // Update OLDPWD (previous directory) environment variable if available
    if (vars[2])
        sh_update_env(cmd->environment, "OLDPWD", ft_strdup(vars[2]->values[0]));
    else
        sh_display_error(ERR_VAR_UNSET, "OLDPWD");

    // Get the current working directory and update the PWD environment variable
    newdir = sh_get_pwd();
    if (newdir)
        sh_update_env(cmd->environment, "PWD", newdir);
    else
        sh_display_error(ERR_VAR_UNSET, "PWD");

    return (ERR_NONE);
}
