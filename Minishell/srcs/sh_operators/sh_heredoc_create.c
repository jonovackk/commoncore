/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_heredoc_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:06:56 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 11:35:22 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sh_heredoc_child_process(char *delimiter, char *temp_file, int fd)
{
	int	error_code;

	rl_catch_signals = 1;
	sh_configure_signal_state(HANDLER_HEREDOC);
	error_code = sh_process_heredoc_line(delimiter, temp_file, fd);
	sh_destroy_tree(sh_command_tree_state(0, NULL));
	sh_destroy_env_list(sh_env_context(NULL));
	rl_clear_history();
	close(fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(error_code);
}

int	sh_create_heredoc(char *delimiter, char *temp_file)
{
	pid_t	heredoc_pid;
	int		fd;
	int		error_code;

	printf(": Creating heredoc with delimiter '%s'\n", delimiter);
	sh_configure_signal_state(HANDLER_IGN);
	fd = open(temp_file, O_CREAT | O_EXCL | O_WRONLY, 0600);
	if (fd == -1)
		return (free(delimiter), free(temp_file), -1);
	heredoc_pid = fork();
	if (heredoc_pid == -1)
	{
		close(fd);
		unlink(temp_file);
		return (free(delimiter), free(temp_file), -1);
	}
	if (heredoc_pid == 0)
		sh_heredoc_child_process(delimiter, temp_file, fd);
	close(fd);
	waitpid(heredoc_pid, &error_code, 0);
	sh_configure_signal_state(HANDLER_INTERRUPT);
	return (sh_handle_heredoc_exit(delimiter, temp_file, error_code));
}
