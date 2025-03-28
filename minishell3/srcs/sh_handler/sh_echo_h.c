#include "../../includes/minishell.h"

int     is_n_option(char *str)
{
    if (!str || *str != '-')
        return (0);
    str++;
    if (!*str)
        return (0);
    while (*str == 'n')
        str++;
    return (!*str);
}

int     echo_builtin(t_sh_cmd *command)
{
    char    **arguments;
    char    *output_msg;
    int     print_newline;

    arguments = command->arguments + 1;
    output_msg = NULL;
    print_newline = 1;
    if (arguments)
    {
        while (*arguments && is_n_option(*arguments))
            arguments++;
        if (arguments != command->arguments + 1)
            print_newline = 0;
        output_msg = join_str_array(arguments, ft_strdup(" "), 0b10);
        ft_dprintf(command->outfile, "%s", output_msg);
    }
    if (print_newline)
        ft_dprintf(command->outfile, "\n");
    free(output_msg);
    return (ERR_NONE);
}