/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_sig_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:50 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:08:51 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_shell_exit_status;

void	sh_signal_ignore(int signal)
{
	(void)signal;
}

void	sh_signal_interactive(int signal)
{
	if (signal == SIGINT)
	{
		g_shell_exit_status = 130;
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sh_signal_quote_mode(int signal)
{
	int	fd;

	printf("\001\033[%dC\002", (int)ft_strlen(rl_prompt) + rl_point - 15);
	if (signal == SIGINT)
	{
		printf("^C\n");
		free(sh_double_quote_state(NULL, 0));
		fd = *(int *)sh_double_quote_state(NULL, 1);
		sh_close_multiple_fd(4, fd, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
		g_shell_exit_status = 130;
		exit(130);
	}
}

void	sh_signal_heredoc_mode(int signal)
{
	int	fd;

	printf("\001\033[%dC\002", (int)ft_strlen(rl_prompt) + rl_point - 15);
	if (signal == SIGINT)
	{
		printf("^C\n");
		unlink(sh_heredoc_state(NULL, 0));
		sh_destroy_env_list(sh_env_context(NULL));
		free(sh_heredoc_state(NULL, 0));
		free(sh_heredoc_state(NULL, 1));
		fd = *(int *)sh_heredoc_state(NULL, 2);
		sh_close_multiple_fd(4, fd, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
		g_shell_exit_status = 130;
		exit(130);
	}
}

void	sh_configure_signal_state(int mode)
{
	static struct termios	terminal_settings;
	static void				(*signal_handlers[4])(int) = {
		sh_signal_ignore,
		sh_signal_interactive,
		sh_signal_quote_mode,
		sh_signal_heredoc_mode
	};

	tcgetattr(STDIN_FILENO, &terminal_settings);
	if (mode == 0)
		terminal_settings.c_lflag |= ECHOCTL;
	else
		terminal_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal_settings);
	signal(SIGINT, signal_handlers[mode]);
	signal(SIGQUIT, signal_handlers[mode]);
}
