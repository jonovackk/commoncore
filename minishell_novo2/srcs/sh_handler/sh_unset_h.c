/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset_h.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:18 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:06:19 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Removes environment variables specified in command arguments
 * 
 * Iterates through command arguments and removes corresponding 
 * environment variables
 * 
 * @param cmd Command containing arguments to unset
 * @return Error status (typically no error)
 */
int sh_execute_unset(t_sh_cmd *cmd)
{
    char **current_arg;
    // start from second argument (first is 'unset' command)
    current_arg = cmd->arguments + 1;
    // remove each specified variable from environment
    while (*current_arg)
        sh_delete_env(cmd->environment, *(current_arg++));
    return (ERR_NONE);
}