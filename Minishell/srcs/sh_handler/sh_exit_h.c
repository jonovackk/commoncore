/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:45 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:05:46 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_shell_exit_status;

long	sh_exit_status_atoi(char *str)
{
	long	n;
	int		sign;

	n = 0;
	sign = 0;
	while (isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*(str++) == '-');
	while (ft_isdigit(*str))
		n = n * 10 + (*str++ - '0');
	if (sign)
		return ((256 - n) % 256);
	return (n % 256);
}

void	sh_handle_exit(int exit_code, t_error_t ec, t_sh_cmd *cmd)
{
	char	*msg;

	if (ec == ERR_NOT_A_NUMBER)
	{
		msg = ft_strjoin("exit: ", cmd->arguments[1], NULL, 0b00);
		sh_display_error(ERR_NOT_A_NUMBER, msg);
		free(msg);
	}
	if (ec == ERR_TOO_MANY_ARGS)
	{
		sh_display_error(ERR_TOO_MANY_ARGS, "exit");
		return ;
	}
	rl_clear_history();
	if (cmd)
		sh_destroy_env_list(*(cmd->environment));
	sh_destroy_tree(sh_command_tree_state(0, NULL));
	exit(exit_code);
}

static int	validate_exit_args(int argc, char *arg, t_sh_cmd *cmd)
{
	if (!ft_is_numeric(arg))
	{
		free(arg);
		sh_handle_exit(ERR_ERRORS, ERR_NOT_A_NUMBER, cmd);
	}
	if (argc > 1)
	{
		free(arg);
		sh_handle_exit(ERR_FAIL_GENERAL, ERR_TOO_MANY_ARGS, cmd);
		return (1);
	}
	sh_handle_exit(sh_exit_status_atoi(arg), ERR_NONE, cmd);
	free(arg);
	return (0);
}

int	sh_execute_exit(t_sh_cmd *cmd)
{
	int		argc;
	char	*arg;

	arg = NULL;
	argc = 0;
	if (cmd)
		argc = ft_tab_len(cmd->arguments) - 1;
	else
		ft_dprintf(2, "exit\n");
	if (!cmd || !argc)
		sh_handle_exit(g_shell_exit_status, ERR_NONE, cmd);
	arg = ft_strdup(cmd->arguments[1]);
	sh_rmv_quotes(&arg, 0);
	return (validate_exit_args(argc, arg, cmd));
}
