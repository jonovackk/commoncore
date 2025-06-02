/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quote_pt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:21 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 11:50:54 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*sh_opendquote(int tmp_fd, t_quote_state quote_state)
{
	char	*line;

	if (quote_state == QUOTE_SINGLE)
		line = readline("quote> ");
	if (quote_state == QUOTE_DOUBLE)
		line = readline("dquote> ");
	write(tmp_fd, "\n", 1);
	write(tmp_fd, line, ft_strlen(line));
	return (line);
}

char	*sh_get_dquote_line(char *line, char *tmp_file, int status)
{
	char	*result;
	int		tmp_fd;

	tmp_fd = open(tmp_file, O_RDONLY);
	result = NULL;
	g_shell_exit_status = WEXITSTATUS(status);
	line = get_next_line(tmp_fd);
	while (line)
	{
		result = ft_strjoin(result, line, NULL, 0b11);
		line = get_next_line(tmp_fd);
	}
	close(tmp_fd);
	unlink(tmp_file);
	return (result);
}

int	sh_get_dquote(char *line, t_sh_env **env, char *tmp)
{
	int		tmp_fd;
	pid_t	quote_pid;

	quote_pid = fork();
	if (quote_pid == -1)
		return (-1);
	if (quote_pid == 0)
	{
		rl_catch_signals = 1;
		sh_configure_signal_state(HANDLER_DQUOTE);
		tmp_fd = open(tmp, O_CREAT | O_EXCL | O_WRONLY, 0600);
		sh_double_quote_state((char *)&tmp_fd, 1);
		rl_clear_history();
		sh_destroy_env_list(*env);
		free(tmp);
		write(tmp_fd, line, ft_strlen(line));
		sh_handle_unclosed_quotes(&line, tmp_fd, QUOTE_NONE);
		free(line);
		sh_close_multiple_fd(4, tmp_fd, STDIN_FILENO, STDOUT_FILENO,
			STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	free(line);
	waitpid(quote_pid, &tmp_fd, 0);
	return (tmp_fd);
}

static char	*sh_process_dquote(char *line, t_sh_env **env,
					char *dquote_file, int *status)
{
	char	*result;

	if (sh_detect_quotes(line, NULL, QUOTE_NONE))
	{
		*status = sh_get_dquote(line, env, dquote_file);
		result = sh_get_dquote_line(line, dquote_file, *status);
	}
	else
		result = line;
	return (result);
}

t_error_t	sh_quote_handler(char **line, t_sh_env **env, int status)
{
	char	*dquote_file;
	char	*history_line;
	char	*quote_str;

	if (!*line)
		return (ERR_ERRORS);
	history_line = *line;
	dquote_file = generate_temp_filename(".dquote", 16);
	history_line = sh_process_dquote(*line, env, dquote_file, &status);
	add_history(history_line);
	free(dquote_file);
	*line = history_line;
	if (WEXITSTATUS(status) == 130)
	{
		free(*line);
		return (ERR_FAIL_GENERAL);
	}
	quote_str = ft_strdup(" ");
	if (sh_detect_quotes(*line, quote_str, QUOTE_NONE))
		sh_display_error(ERR_DQUOTE_ABORTED, quote_str);
	free(quote_str);
	return (ERR_NONE);
}
