/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:30 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:08:31 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sh_env	*sh_env_context(t_sh_env **env)
{
	static t_sh_env	*env_ctx;

	if (!env_ctx || env)
		env_ctx = *env;
	return (env_ctx);
}

void	sh_env_defaults(t_sh_env **env, char **argv)
{
	char	*tmp;

	sh_update_env(env, "OLDPWD", NULL);
	tmp = sh_get_pwd();
	if (tmp)
		sh_update_env(env, "PWD", tmp);
	tmp = ft_strjoin(sh_get_pwd(), argv[0], "/", 0b01);
	if (tmp)
		sh_update_env(env, "_", tmp);
}

static void	sh_update_special_envs(t_sh_env **env, char **argv, int env_count)
{
	char		*tmp;

	(void)argv;
	if (sh_find_env(*env, "SHLVL") && sh_find_env(*env, "SHLVL")->values)
		tmp = ft_itoa(1 + ft_atoi(sh_find_env(*env, "SHLVL")->values[0]));
	else
		tmp = ft_strdup("1");
	if (tmp)
		sh_update_env(env, "SHLVL", tmp);
	if (env_count)
	{
		tmp = ft_strdup("minishell");
		if (tmp)
			sh_update_env(env, "SHELL", tmp);
	}
}

t_sh_env	*sh_env_init(char **argv, char **envp)
{
	t_sh_env	*env;
	int			i;

	i = -1;
	env = NULL;
	while (envp[++i])
		sh_append_env(&env, sh_create_env_var(envp[i]));
	if (i == 0)
		sh_env_defaults(&env, argv);
	sh_update_special_envs(&env, argv, i);
	return (env);
}
