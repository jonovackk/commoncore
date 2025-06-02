/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_mf_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:05 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 12:09:49 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_error_t	sh_heredoc_init(t_sh_cmd *cmd)
{
	t_error_t		err;
	t_sh_redir		*tmp;
	char			*hd_file;

	err = ERR_NONE;
	tmp = cmd->redirects;
	while (tmp && cmd->heredoc_fd != -1)
	{
		if (tmp->mode == REDIR_HEREDOC)
		{
			hd_file = generate_temp_filename(".heredoc", 16);
			if (cmd->heredoc_fd > 2)
				close(cmd->heredoc_fd);
			cmd->heredoc_fd = sh_create_heredoc(ft_strdup(tmp->target),
					hd_file);
			if (cmd->heredoc_fd == FILE_HEREDOC_TEMP)
				return (ERR_HEREDOC_ABORTED);
		}
		tmp = tmp->next;
	}
	return (cmd->heredoc_fd == FILE_ERROR);
}

t_error_t	sh_line_expand(t_sh_cmd *cmd, char **file)
{
	char	**files;
	char	*var;

	var = ft_strdup(*file);
	sh_replace_env_vars(*cmd->environment, file, QUOTE_NONE);
	if (sh_contains_unquoted_wildcard(*file, QUOTE_NONE))
		sh_replace_wildcards(file);
	files = ft_split(*file, ' ');
	if (ft_tab_len(files) > 1)
	{
		sh_display_error(ERR_AMBIGUOUS_REDIRECT, var);
		free(var);
		free(*file);
		ft_free_tab((void **)files);
		return (ERR_AMBIGUOUS_REDIRECT);
	}
	free(var);
	ft_free_tab((void **)files);
	return (ERR_NONE);
}

t_error_t	sh_heredoc_write(t_sh_cmd *cmd, char *file, int mode)
{
	int	*fd;

	if (sh_line_expand(cmd, &file))
		return (ERR_AMBIGUOUS_REDIRECT);
	if (mode == FILE_MODE_READ)
		fd = &(cmd->input_fd);
	else
		fd = &(cmd->output_fd);
	if (*fd > 2)
		close(*fd);
	if (mode != FILE_MODE_READ && *fd != FILE_ERROR)
		*fd = open(file, mode, 0644);
	else if (*fd != -1)
		*fd = open(file, mode);
	if (*fd == -1)
	{
		if (errno == ENFILE)
			sh_display_error(ERR_FD_LIMIT, file);
		else
			sh_display_error(ERR_NO_ENTRY, file);
		free(file);
		return (ERR_FD_LIMIT);
	}
	free(file);
	return (ERR_NONE);
}

t_error_t	sh_output_load(t_sh_cmd *cmd)
{
	t_sh_redir		*tmp;
	t_error_t		op;

	tmp = cmd->redirects;
	op = ERR_NONE;
	while (tmp && cmd->output_fd != FILE_ERROR && op == ERR_NONE)
	{
		if (tmp->mode == REDIR_INPUT && access(tmp->target, R_OK))
			break ;
		if (tmp->mode == REDIR_OUTPUT)
			op = sh_heredoc_write(cmd, ft_strdup(tmp->target),
					FILE_MODE_WRITE_CREATE);
		else if (tmp->mode == REDIR_APPEND)
			op = sh_heredoc_write(cmd, ft_strdup(tmp->target),
					FILE_MODE_WRITE_APPEND);
		tmp = tmp->next;
	}
	if (op == ERR_FD_LIMIT || op == ERR_AMBIGUOUS_REDIRECT)
		return (op);
	if (tmp == NULL)
		return (cmd->output_fd == FILE_ERROR);
	return (cmd->output_fd == FILE_ERROR && access(tmp->target, R_OK));
}

t_error_t	sh_input_load(t_sh_cmd *cmd, int *hd_last)
{
	t_sh_redir		*tmp;
	t_error_t		op;

	if (!cmd->redirects)
		return (ERR_NONE);
	tmp = cmd->redirects;
	op = ERR_NONE;
	*hd_last = 0;
	while (tmp && cmd->input_fd != FILE_ERROR && op == ERR_NONE)
	{
		if (tmp->mode == REDIR_INPUT)
		{
			*hd_last = 0;
			op = sh_heredoc_write(cmd, ft_strdup(tmp->target), FILE_MODE_READ);
		}
		if (tmp->mode != REDIR_OUTPUT && tmp->mode != REDIR_APPEND)
			*hd_last |= (tmp->mode == REDIR_HEREDOC);
		tmp = tmp->next;
	}
	if (op == ERR_FD_LIMIT || op == ERR_AMBIGUOUS_REDIRECT)
		return (op);
	return (cmd->input_fd == FILE_ERROR);
}
