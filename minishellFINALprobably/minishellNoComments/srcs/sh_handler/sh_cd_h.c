/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:23 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/19 11:30:37 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_dir_vars(t_sh_env *envp, t_sh_env **dir_vars)
{
	dir_vars[0] = sh_find_env(envp, "HOME");
	dir_vars[1] = sh_find_env(envp, "OLDPWD");
	dir_vars[2] = sh_find_env(envp, "PWD");
	dir_vars[3] = NULL;
}

t_error_t	sh_change_directory(char *target)
{
	if (!target)
		return (ERR_FAIL_GENERAL);
	if (chdir(target) == -1)
	{
		if (errno == EACCES)
			sh_display_error(ERR_NO_PERMISS, target);
		else
			sh_display_error(ERR_NO_ENTRY, target);
		return (ERR_FAIL_GENERAL);
	}
	return (ERR_NONE);
}

static char	*get_target(int argc, char **argv, t_sh_env **vars, int out)
{
	if (argc == 0)
	{
		if (!vars[0] || !vars[0]->values || !vars[0]->values[0])
			return (ft_dprintf(out, "cd: HOME not set\n"), NULL);
		return (vars[0]->values[0]);
	}
	if (argc == 1)
	{
		if (ft_strncmp(argv[0], "~", 2) == 0)
		{
			if (!vars[0] || !vars[0]->values || !vars[0]->values[0])
				return (ft_dprintf(out, "cd: HOME not set\n"), NULL);
			return (vars[0]->values[0]);
		}
		if (ft_strncmp(argv[0], "-", 2) == 0)
		{
			if (!vars[1] || !vars[1]->values || !vars[1]->values[0])
				return (ft_dprintf(out, "cd: OLDPWD not set\n"), NULL);
			ft_dprintf(out, "\033[37;1m-> %s\033[0m\n", vars[1]->values[0]);
			return (vars[1]->values[0]);
		}
		return (argv[0]);
	}
	return (NULL);
}

t_error_t	sh_cd_target(int argc, char **argv, t_sh_env **vars, int out)
{
	char	*target;

	target = get_target(argc, argv, vars, out);
	if (!target)
		return (ERR_FAIL_GENERAL);
	return (sh_change_directory(target));
}

int	sh_execute_cd(t_sh_cmd *cmd)
{
	int			argc;
	char		*newdir;
	t_sh_env	*vars[4];

	argc = ft_tab_len(cmd->arguments);
	if (argc > 2)
		sh_display_error(ERR_TOO_MANY_ARGS, "cd");
	sh_dir_vars(*(cmd->environment), (t_sh_env **)&vars);
	if ((argc - 1) && !vars[0])
		sh_display_error(ERR_VAR_UNSET, "HOME");
	else if (sh_cd_target(argc - 1, cmd->arguments + 1, vars, cmd->output_fd))
		return (ERR_FAIL_GENERAL);
	if (vars[2])
		sh_update_env(cmd->environment, "OLDPWD",
			ft_strdup(vars[2]->values[0]));
	else
		sh_display_error(ERR_VAR_UNSET, "OLDPWD");
	newdir = sh_get_pwd();
	if (newdir)
		sh_update_env(cmd->environment, "PWD", newdir);
	else
		sh_display_error(ERR_VAR_UNSET, "PWD");
	return (ERR_NONE);
}
