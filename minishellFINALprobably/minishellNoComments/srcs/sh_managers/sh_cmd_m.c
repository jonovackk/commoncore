/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:53 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 14:37:39 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*sh_search_in_path(char *bin, char **paths, char *cmd)
{
	int		i;
	char	*candidate;

	i = 0;
	while (paths[i])
	{
		candidate = ft_strjoin(paths[i], bin, 0, 0b00);
		if (candidate)
		{
			if (access(candidate, X_OK) == 0)
			{
				free(bin);
				return (candidate);
			}
			free(candidate);
		}
		i++;
	}
	free(bin);
	return (ft_strdup(cmd));
}

char	*sh_find_path(char *cmd, t_sh_env *env)
{
	char	*bin;

	if (!cmd)
		return (ft_strdup(""));
	if (!*cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (env && ft_strncmp(env->key, "PATH", 5))
		env = env->next;
	if (!env || !env->values || !env->values[0])
		return (ft_strjoin("/", cmd, 0, 0b00));
	bin = ft_strjoin("/", cmd, 0, 0b00);
	if (!bin)
		return (NULL);
	return (sh_search_in_path(bin, env->values, cmd));
}

void	sh_free_cmd(t_sh_cmd *cmd)
{
	sh_clear_redir_list(cmd->redirects);
	free(cmd->executable);
	ft_free_tab((void **)cmd->arguments);
	free(cmd);
}
