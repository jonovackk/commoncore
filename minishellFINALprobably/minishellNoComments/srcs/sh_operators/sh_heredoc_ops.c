/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_heredoc_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:58 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 15:50:22 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_shell_exit_status;

void	sh_handle_heredoc_limit(t_sh_token *tokens, t_sh_env **environment)
{
	sh_display_error(ERR_HEREDOC_LIMIT, NULL);
	sh_free_token_list(tokens);
	sh_destroy_env_list(*environment);
	exit(ERR_ERRORS);
}

void	sh_parse_heredoc_line(char **line, int fd, int expand)
{
	static int	first_line = 1;

	if (expand)
		sh_replace_env_vars(sh_env_context(NULL), line, QUOTE_IGNORE);
	write(fd, *line, ft_strlen(*line));
	if (!first_line)
		write(fd, "\n", 1);
	first_line = 0;
	free(*line);
	*line = readline(PROMPT_HEREDOC);
}

int	sh_process_heredoc_line(char *delimiter, char *temp_file, int fd)
{
	char	*line;
	int		should_expand;

	if (fd == -1)
	{
		free(delimiter);
		return (ERR_FAIL_GENERAL);
	}
	should_expand = !(ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''));
	sh_rmv_quotes(&delimiter, QUOTE_NONE);
	sh_heredoc_state(temp_file, 0);
	sh_heredoc_state(delimiter, 1);
	sh_heredoc_state((char *)&fd, 2);
	line = readline(PROMPT_HEREDOC);
	while (line && strcmp(line, delimiter) != 0 && !access(temp_file, F_OK))
	{
		if (should_expand)
			sh_replace_env_vars(sh_env_context(NULL), &line, QUOTE_IGNORE);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(PROMPT_HEREDOC);
	}
	free(delimiter);
	free(temp_file);
	if (!line)
		return (ERR_FAIL_GENERAL);
	free(line);
	return (ERR_NONE);
}

int	sh_handle_heredoc_exit(char *delimiter, char *temp_file, int exit_status)
{
	int	fd;

	exit_status = WEXITSTATUS(exit_status);
	if (exit_status == 1)
	{
		sh_rmv_quotes(&delimiter, QUOTE_NONE);
		sh_display_error(ERR_HEREDOC_ABORTED, delimiter);
	}
	else if (exit_status == 130)
	{
		unlink(temp_file);
		free(delimiter);
		free(temp_file);
		g_shell_exit_status = 130;
		return (FILE_HEREDOC_TEMP);
	}
	fd = open(temp_file, O_RDONLY);
	unlink(temp_file);
	free(delimiter);
	free(temp_file);
	return (fd);
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
	{
		free(delimiter);
		free(temp_file);
		return (-1);
	}
	heredoc_pid = fork();
	if (heredoc_pid == -1)
	{
		close(fd);
		unlink(temp_file);
		free(delimiter);
		free(temp_file);
		return (-1);
	}
	if (heredoc_pid == 0)
	{
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
	close(fd);
	waitpid(heredoc_pid, &error_code, 0);
	sh_configure_signal_state(HANDLER_INTERRUPT);
	return (sh_handle_heredoc_exit(delimiter, temp_file, error_code));
}
