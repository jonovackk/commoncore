/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:53 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:06:54 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*sh_find_path(char *cmd, t_sh_env *env)
{
	int		i;
	char	*path;
	char	*bin;

	if (!cmd)
		return (ft_strdup(""));

	if (!*cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));

	// Find the PATH entry
	while (env && ft_strncmp(env->key, "PATH", 5))
		env = env->next;

	// If PATH is not found, return default /cmd
	if (!env || !env->values || !env->values[0])
		return (ft_strjoin("/", cmd, 0, 0b00));

	// Join the "/cmd" part once
	bin = ft_strjoin("/", cmd, 0, 0b00);
	if (!bin)
		return (NULL);

	// Iterate through PATH entries
	i = 0;
	path = NULL;

	while (env->values[i])
	{
		if (!env->values[i]) {
			i++;
			continue;
		}

		char *candidate = ft_strjoin(env->values[i], bin, 0, 0b00);
		if (!candidate) {
			i++;
			continue;
		}

		if (access(candidate, X_OK) == 0)
		{
			free(bin);
			return (candidate);
		}
		free(candidate);
		i++;
	}

	free(bin);
	return (ft_strdup(cmd)); // Fallback: return cmd as-is if no match found
}


void	sh_free_cmd(t_sh_cmd *cmd)
{
	sh_clear_redir_list(cmd->redirects);
	free(cmd->executable);
	ft_free_tab((void **)cmd->arguments);
	free(cmd);
}