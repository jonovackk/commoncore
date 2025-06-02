/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:44 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:06:45 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_shell_exit_status;

int	sh_get_env_var_length(char *str)
{
	char	*ptr;

	ptr = str + 1;
	if (!*ptr)
		return (1);
	if (ft_isdigit(*ptr) || ft_strchr("\"'", *ptr))
		return (2);
	if (!ft_strchr("_?", *ptr) && !ft_isalnum(*ptr))
		return (1);
	if (*ptr == '?')
		return (2);
	ptr++;
	while (*ptr && (ft_isalnum(*ptr) && !ft_strchr("_?", *ptr)))
		ptr++;
	return (ptr - str);
}

void	sh_process_quoted_section(char **s, int *rem, t_quote_state *state)
{
	while (*s && **s && ((*rem) > 0))
	{
		sh_update_quote_state(*((*s)++), state);
		(*rem)--;
	}
}

void	sh_insert_env_vars(t_sh_env *env, char *s, char ***res_parts,
		t_quote_state state)
{
	t_sh_env	*env_var;
	char		*key;
	int			key_len;

	(void)state;
	if (*s && *(s + 1) == '?')
	{
		ft_strapp(res_parts, ft_itoa(g_shell_exit_status));
		return ;
	}
	s++;
	if (ft_isdigit(*s))
		return ;
	key_len = sh_get_env_var_length(s - 1);
	if (ft_strchr("\"'", *s))
		ft_strapp(res_parts, ft_strndup(s - 1, 2));
	if (ft_strchr("\"'", *s))
		return ;
	key = ft_strndup(s, key_len - 1);
	env_var = sh_find_env(env, key);
	if (!env_var)
		ft_strapp(res_parts, ft_strdup(""));
	else
		ft_strapp(res_parts, sh_format_env_var(env_var, 0, 0));
	free(key);
}

void	sh_replace_env_vars(t_sh_env *env, char **line, t_quote_state state)
{
	int		seg_len;
	char	*ptr;
	char	**parts;

	ptr = *line;
	parts = NULL;
	if (!ptr)
		return ;
	while (*ptr)
	{
		seg_len = ft_strcspn(ptr, "$");
		ft_strapp(&parts, ft_strndup(ptr, seg_len));
		sh_process_quoted_section(&ptr, &seg_len, &state);
		if (!*ptr)
			break ;
		if (state != QUOTE_SINGLE && sh_get_env_var_length(ptr) > 1)
			sh_insert_env_vars(env, ptr, &parts, state);
		else
			ft_strapp(&parts, ft_strndup(ptr, sh_get_env_var_length(ptr)));
		ptr += sh_get_env_var_length(ptr);
	}
	free(*line);
	*line = ft_strsjoin(parts, NULL, 0b01);
}
