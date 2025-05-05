#include "../../includes/minishell.h"

/**
 * @brief Checks if the string represents the `-n` option flag
 * 
 * What it does:
 * - The function checks if the input string starts with `-n` and ensures that it doesn't contain anything else.
 * - It is typically used to check options like `-n` in commands (e.g., `echo -n`).
 * 
 * @param str The string to check.
 * @return 1 if the string represents the `-n` option, 0 otherwise.
 */
int sh_n_option(char *str)
{
    // Check if the string is NULL or does not start with '-'
    if (!str || *str != '-')
        return (0);

    // Move past the '-' character
    str++;

    // Check if the string is empty after the '-'
    if (!*str)
        return (0);

    // Check if the string consists only of 'n' characters
    while (*str == 'n')
        str++;

    // Return 1 if we reached the end of the string (only 'n' characters were present), otherwise return 0
    return (!*str);
}


/**
 * @brief Executes the built-in `echo` command, printing the provided message.
 * 
 * What it does:
 * - Checks if the `-n` option is provided to prevent printing a newline.
 * - Joins the arguments to form the output message.
 * - Prints the message to the specified output, followed by a newline unless `-n` was specified.
 * 
 * @param command The command structure containing the arguments and output file descriptor.
 * @return ERR_NONE on success.
 */
int sh_echo_execute(t_sh_cmd *command)
{
    char    **arguments;
    char    *output_msg;
    int     print_newline;

    // Get the arguments passed to the echo command, skipping the command name
    arguments = command->arguments + 1;
    output_msg = NULL;
    print_newline = 1;

    // Loop through arguments to check for the -n option
    if (arguments)
    {
        while (*arguments && sh_n_option(*arguments))  // Check for -n option
            arguments++;

        // If any -n options were found, set print_newline to 0 (no newline)
        if (arguments != command->arguments + 1)
            print_newline = 0;

        // Join the remaining arguments into a single string
        output_msg = ft_strsjoin(arguments, ft_strdup(" "), 0b10);

        // Print the joined output message to the specified output
        ft_dprintf(command->output_fd, "%s", output_msg);
    }

    // If print_newline is still 1, print a newline at the end
    if (print_newline)
        ft_dprintf(command->output_fd, "\n");

    // Free the allocated memory for the output message
    free(output_msg);

    return (ERR_NONE);  // Return success
}
