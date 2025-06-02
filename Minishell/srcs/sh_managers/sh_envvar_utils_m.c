/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_envvar_utils_m.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:06 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 14:28:06 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sh_env	*sh_find_env(t_sh_env *env, char *key)
{
	while (env && ft_strncmp(env->key, key, ft_strlen(env->key) + 1))
		env = env->next;
	return (env);
}

t_sh_env	*sh_get_last_env(t_sh_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	sh_update_env(t_sh_env **env, char *key, char *val)
{
	char		*safe_val;
	t_sh_env	*head;

	if (val != NULL)
		safe_val = val;
	else
		safe_val = "";
	head = *env;
	while (*env && ft_strncmp((*env)->key, key, ft_strlen(key) + 1))
		*env = (*env)->next;
	if (!*env)
	{
		sh_append_env(&head, sh_create_env_var(key));
		*env = sh_get_last_env(head);
	}
	ft_free_tab((void **)(*env)->values);
	(*env)->values = ft_split(safe_val, ':');
	*env = head;
	if (val != NULL)
		free(val);
}

void	sh_extend_env(t_sh_env **env, char *key, char *val)
{
	t_sh_env	*head;
	char		*tmp;

	head = *(env);
	key[ft_strlen(key) - 1] = 0;
	while (*(env) && ft_strncmp((*env)->key, key, ft_strlen(key)))
		*(env) = (*env)->next;
	tmp = sh_format_env_var(*env, 0, 0);
	tmp = ft_strjoin(tmp, val, NULL, 0b11);
	sh_update_env(&head, key, tmp);
	*(env) = head;
}
