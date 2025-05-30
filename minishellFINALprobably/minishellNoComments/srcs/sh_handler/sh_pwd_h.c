/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pwd_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:13 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:06:14 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_shell_exit_status;

char	*sh_trim_pwd(char *str)
{
	char	*last_slash;

	last_slash = ft_strrchr(str, '/');
	if (!last_slash)
		return (ft_strdup(""));
	return (ft_strdup(last_slash));
}

char	*sh_get_pwd(void)
{
	char	cwd[65536];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (NULL);
}

int	sh_execute_pwd(t_sh_cmd *cmd)
{
	char	cwd[65536];

	if (getcwd(cwd, sizeof(cwd)))
		ft_dprintf(cmd->output_fd, "%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (ERR_FAIL_GENERAL);
	}
	return (ERR_NONE);
}

char	*sh_get_prompt(t_sh_env *envp)
{
	char	*result;
	char	*cwd;
	char	*tmp;

	if (!envp)
		return (ft_strdup("Minishell$ "));
	cwd = sh_get_pwd();
	if (!cwd)
		return (ft_strdup("Minishell$ "));
	if (g_shell_exit_status == 0)
		tmp = ft_strjoin(cwd, PROMPT_SUCCESS, " ", 0);
	else
		tmp = ft_strjoin(cwd, PROMPT_FAIL, " ", 0);
	free(cwd);
	if (!tmp)
		return (ft_strdup("Minishell$ "));
	result = ft_strjoin(tmp, PROMPT_TAIL, "", 0b01);
	if (!result)
	{
		free(tmp);
		return (ft_strdup("Minishell$ "));
	}
	return (result);
}
