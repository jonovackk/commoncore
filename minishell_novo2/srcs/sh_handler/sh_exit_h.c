/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:45 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:05:46 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int  g_shell_exit_status;

/**
 * @brief Converts a string to a long integer, returning it as a valid exit status code.
 * 
 * What it does:
 * - Parses the string to convert it into a number.
 * - Handles optional leading spaces, sign (`+` or `-`), and ensures the result is in the 0-255 range for exit codes.
 * - If the sign is negative, it adjusts the value to fit within the exit status range (0-255).
 * 
 * @param str The string to be converted.
 * @return The resulting value modulo 256, ensuring the exit code is within the valid range.
 */
long sh_exit_status_atoi(char *str)
{
    long    n;
    int     sign;

    n = 0;
    sign = 0;

    // Skip leading spaces
    while (isspace(*str))
        str++;

    // Check for optional sign and handle it
    if (*str == '-' || *str == '+')
        sign = (*(str++) == '-');

    // Convert the numeric part of the string to a long
    while (ft_isdigit(*str))
        n = n * 10 + (*str++ - '0');

    // If the sign is negative, adjust the result to fit in the range 0-255
    if (sign)
        return ((256 - n) % 256);

    // Return the value modulo 256 to ensure it is within the valid exit status range (0-255)
    return (n % 256);
}


/**
 * @brief Handles the exit process, including error reporting and resource cleanup.
 * 
 * What it does:
 * - If the error code is `ERR_NAN`, it prints an error message indicating the non-numeric argument.
 * - If the error code is `ERR_ARGS`, it prints an error message for invalid `exit` arguments and returns.
 * - Clears the readline history, destroys the environment list, and cleans up the shell's internal structures.
 * - Finally, it exits the program with the specified exit code.
 * 
 * @param exit_code The exit code to be returned by the program.
 * @param ec The error type to handle.
 * @param cmd The command structure containing the arguments for the `exit` command.
 */
void sh_handle_exit(int exit_code, error_t ec, t_sh_cmd *cmd)
{
    char    *msg;

    // Handle non-numeric argument error (ERR_NAN)
    if (ec == ERR_NOT_A_NUMBER)
    {
        msg = ft_strjoin("exit: ", cmd->arguments[1], NULL, 0b00);
        sh_display_error(ERR_NOT_A_NUMBER, msg);
        free(msg);
    }

    // Handle invalid arguments for the `exit` command (ERR_ARGS)
    if (ec == ERR_TOO_MANY_ARGS)
    {
        sh_display_error(ERR_TOO_MANY_ARGS, "exit");
        return;
    }

    // Clear the readline history
    rl_clear_history();

    // Destroy the environment list if the command is not NULL
    if (cmd)
        sh_destroy_env_list(*(cmd->environment));

    // Destroy the shell's internal tree structure
    sh_destroy_tree(sh_command_tree_state(0, NULL));

    // Exit the program with the specified exit code
    exit(exit_code);
}


/**
 * @brief Implements the `exit` built-in command for the shell.
 * 
 * What it does:
 * - Checks if there are arguments passed to the `exit` command.
 * - Handles various error cases (non-numeric exit codes, too many arguments).
 * - Cleans up resources and exits the shell with the appropriate exit code.
 * 
 * @param cmd The command structure containing the arguments passed to the `exit` command.
 * @return 1 if there were too many arguments, otherwise it exits the program.
 */
int sh_execute_exit(t_sh_cmd *cmd)
{
    int argc;

    argc = 0;
    
    // Determine the number of arguments passed to the `exit` command
    if (cmd)
        argc = ft_tab_len(cmd->arguments) - 1;
    else
        ft_dprintf(2, "exit\n");

    // If no arguments are passed, exit with the global exit code
    if (!cmd || !argc)
        sh_handle_exit(g_shell_exit_status, ERR_NONE, cmd);

    // If the argument is non-numeric, print an error and exit
    if (!ft_is_numeric(cmd->arguments[1]))
        sh_handle_exit(ERR_ERRORS, ERR_NOT_A_NUMBER, cmd);

    // If there are too many arguments, print an error and exit
    if (argc > 1)
        sh_handle_exit(ERR_FAIL_GENERAL, ERR_TOO_MANY_ARGS, cmd);

    // If there's a valid numeric argument, convert and exit with the appropriate code
    sh_handle_exit(sh_exit_status_atoi(cmd->arguments[1]), ERR_NONE, cmd);

    // Return 1 if there were too many arguments (though this is never reached because exit is called)
    return (argc > 1);
}
