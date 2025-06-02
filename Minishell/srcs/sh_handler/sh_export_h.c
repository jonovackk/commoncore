/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:49 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 11:57:14 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_export_syntax(char *str)
{
	char	*tmp;

	tmp = str;
	if (ft_isdigit(*str) || !*str)
		return (0);
	while (*str && (ft_isalnum(*str) || *str == '_') && *str != '=')
		str++;
	if (*str == '+' && *(str + 1) == '=')
		return (1);
	return ((tmp != str && *str == '=') || !*str);
}

int	sh_display_expor_var(t_sh_cmd *cmd)
{
	char	**env_array;
	char	**tmp;
	char	*line;

	env_array = sh_create_env_array(*(cmd->environment), 1);
	if (!env_array)
		return (ERR_FAIL_GENERAL);
	ft_sort_strs_tab(env_array, ft_tab_len(env_array));
	tmp = env_array;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, "_=", 2))
		{
			line = ft_strjoin("declare -x ", *tmp, NULL, 0);
			ft_dprintf(cmd->output_fd, "%s\n", line);
			free(line);
		}
		tmp++;
	}
	ft_free_tab((void **)env_array);
	return (ERR_NONE);
}

int	sh_update_env_var(t_sh_cmd *cmd, char *tmp)
{
	char	**var;
	char	*trimmed;

	var = NULL;
	if (ft_strchr(tmp, '='))
	{
		ft_strapp(&var, ft_strndup(tmp, ft_strcspn(tmp, "=")));
		ft_strapp(&var, ft_strdup(tmp + ft_strlen(*var) + 1));
		trimmed = ft_strtrim(var[1], "\"");
		free(var[1]);
		var[1] = trimmed;
		if (ft_strlen(var[0]) && var[0][ft_strlen(var[0]) - 1] == '+')
			sh_extend_env(cmd->environment, var[0], ft_strdup(var[1]));
		else
		{
			if (var[1])
				sh_update_env(cmd->environment, var[0], ft_strdup(var[1]));
			else
				sh_update_env(cmd->environment, var[0], "");
		}
		ft_free_tab((void **)var);
	}
	else if (!sh_find_env(*(cmd->environment), tmp))
		sh_update_env(cmd->environment, tmp, NULL);
	return (ERR_NONE);
}

int	sh_execute_export(t_sh_cmd *cmd)
{
	char		**tmp;
	t_error_t	errcode;

	tmp = cmd->arguments;
	errcode = ERR_NONE;
	if (ft_tab_len(tmp) == 1 && sh_display_expor_var(cmd))
		errcode = ERR_FAIL_GENERAL;
	else
	{
		while (*(++tmp))
		{
			if (!sh_export_syntax(*tmp))
			{
				sh_display_error(ERR_INVALID, *tmp);
				errcode = ERR_FAIL_GENERAL;
			}
			if (sh_update_env_var(cmd, *tmp))
				errcode = ERR_FAIL_GENERAL;
		}
	}
	sh_env_context(cmd->environment);
	return (errcode);
}
