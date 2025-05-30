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

int	sh_execute_unset(t_sh_cmd *cmd)
{
	char	**current_arg;

	current_arg = cmd->arguments + 1;
	while (*current_arg)
		sh_delete_env(cmd->environment, *(current_arg++));
	return (ERR_NONE);
}
