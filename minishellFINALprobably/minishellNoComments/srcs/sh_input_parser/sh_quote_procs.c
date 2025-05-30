/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quote_procs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:32 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/13 13:36:05 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int		g_shell_exit_status;

void	sh_handle_unclosed_quotes(char **line, int tmp_fd, t_quote_state state)
{
	char	*orig;
	char	*dq_buf;

	if (!*line)
		return ;
	orig = *line;
	sh_double_quote_state(*line, 0);
	while (**line)
		sh_update_quote_state(*((*line)++), &state);
	if (state)
	{
		dq_buf = sh_opendquote(tmp_fd, state);
		if (!dq_buf)
		{
			free(dq_buf);
			*line = orig;
			return ;
		}
		dq_buf = ft_strjoin(orig, dq_buf, "\n", 0b11);
		sh_handle_unclosed_quotes(&dq_buf, tmp_fd, QUOTE_NONE);
		sh_double_quote_state(dq_buf, 0);
		*line = dq_buf;
		return ;
	}
	*line = orig;
}

t_quote_state	sh_detect_quotes(char *line, char *end_marker,
		t_quote_state state)
{
	while (*line)
		sh_update_quote_state(*(line++), &state);
	if (end_marker && state == QUOTE_SINGLE)
		*end_marker = '\'';
	else if (end_marker && state == QUOTE_DOUBLE)
		*end_marker = '"';
	return (state);
}

static char	*remove_quotes_process(char *src)
{
	char	*dst;
	char	*res_ptr;
	int		in_single;
	int		in_double;

	dst = malloc(strlen(src) + 1);
	if (!dst)
		return (NULL);
	res_ptr = dst;
	in_single = 0;
	in_double = 0;
	while (*src)
	{
		if (*src == '\'' && !in_double)
			in_single = !in_single;
		else if (*src == '\"' && !in_single)
			in_double = !in_double;
		else
			*res_ptr++ = *src;
		src++;
	}
	*res_ptr = '\0';
	return (dst);
}

void	sh_rmv_quotes(char **line, t_quote_state state)
{
	char	*new_line;

	(void)state;
	if (!line || !*line)
		return ;
	new_line = remove_quotes_process(*line);
	if (!new_line)
		return ;
	free(*line);
	*line = new_line;
}
