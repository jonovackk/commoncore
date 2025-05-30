/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:38 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:05:40 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_env_list_size(t_sh_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	*sh_format_env_var(t_sh_env *env, int format, int include_name)
{
	char	*str;

	str = NULL;
	if (env == NULL)
		return (NULL);
	if (!env->values && include_name)
		return (ft_strdup(env->key));
	if (include_name)
		str = ft_strjoin(ft_strdup(env->key), "=", NULL, 0b01);
	if (format)
		str = ft_strjoin(str, "\"", NULL, 1);
	str = ft_strjoin(str, ft_strsjoin(env->values, ":", 0b00), NULL, 0b11);
	if (format)
		str = ft_strjoin(str, "\"", NULL, 0b01);
	return (str);
}

char	**sh_create_env_array(t_sh_env *env, int format)
{
	int		i;
	int		size;
	char	**env_array;

	i = -1;
	size = sh_env_list_size(env) + 1;
	env_array = malloc(size * sizeof(char *));
	if (!env_array)
		return (NULL);
	while (++i < size - 1)
	{
		env_array[i] = sh_format_env_var(env, format, 1);
		if (!env_array[i])
		{
			ft_free_tab((void **)env_array);
			return (NULL);
		}
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	sh_execute_env(t_sh_cmd *cmd)
{
	t_sh_env	*env;
	char		**env_array;
	char		**tmp;

	if (ft_tab_len(cmd->arguments) > 1)
	{
		sh_display_error(ERR_TOO_MANY_ARGS, "env");
		return (126);
	}
	env = *(cmd->environment);
	env_array = sh_create_env_array(env, 0);
	if (!env_array)
		return (ERR_FAIL_GENERAL);
	tmp = env_array;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '='))
			ft_dprintf(cmd->output_fd, "%s\n", *tmp);
		tmp++;
	}
	ft_free_tab((void **)env_array);
	return (ERR_NONE);
}
