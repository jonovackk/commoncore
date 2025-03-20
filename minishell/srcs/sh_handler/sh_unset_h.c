#include "minishell.h"

/**
 * @brief Removes environment variables specified in command arguments
 * 
 * Iterates through command arguments and removes corresponding 
 * environment variables
 * 
 * @param cmd Command containing arguments to unset
 * @return Error status (typically no error)
 */
int sh_unset_variables(t_sh_cmd *cmd)
{
    char **current_arg;
    // start from second argument (first is 'unset' command)
    current_arg = cmd->arguments + 1;
    // remove each specified variable from environment
    while (*current_arg)
        sh_remove_environment_variable(cmd->environment, *(current_arg++));
    return (ERR_NONE);
}