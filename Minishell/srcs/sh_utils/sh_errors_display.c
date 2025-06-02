/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_errors_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:35 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:08:46 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_display_extended_errors(t_error_t error, char *str)
{
	if (error == ERR_NO_COMMAND)
	{
		ft_dprintf(2, "%s", PROMPT_ERROR);
		if (str)
			ft_dprintf(2, "%s", str);
		ft_dprintf(2, ": command not found\n");
	}
	if (error == ERR_BAD_QUOTE)
		ft_dprintf(2, ERR_MSG_SYNTAX_ERROR_QUOTE, PROMPT_ERROR, str);
	if (error == ERR_SYNTAX)
	{
		if (str)
			ft_dprintf(2, ERR_MSG_SYNTAX_ERROR_TOKEN, PROMPT_ERROR, str);
		else
			ft_dprintf(2, ERR_MSG_SYNTAX_ERROR, PROMPT_ERROR);
	}
	if (error == ERR_HEREDOC_LIMIT)
		ft_dprintf(2, ERR_MSG_HEREDOC_LIMIT_EXCEEDED, PROMPT_ERROR);
	if (error == ERR_FD_LIMIT)
		ft_dprintf(2, ERR_MSG_HEREDOC_LIMIT_EXCEEDED, PROMPT_ERROR, str);
	if (error == ERR_AMBIGUOUS_REDIRECT)
		ft_dprintf(2, ERR_MSG_AMBIGUOUS_REDIRECT, PROMPT_ERROR, str);
	ft_dprintf(2, "\001\033[0m\002");
}

void	sh_display_error(t_error_t error, char *str)
{
	if (error == ERR_VAR_UNSET)
		ft_dprintf(2, ERR_MSG_IS_A_DIRECTORY, PROMPT_ERROR, str);
	if (error == ERR_NO_ENTRY)
		ft_dprintf(2, ERR_MSG_NO_SUCH_FILE_OR_DIR, PROMPT_ERROR, str);
	if (error == ERR_TOO_MANY_ARGS)
		ft_dprintf(2, ERR_MSG_TOO_MANY_ARGS, PROMPT_ERROR, str);
	if (error == ERR_NOT_A_NUMBER)
		ft_dprintf(2, ERR_MSG_NUMERIC_ARG_REQUIRED, PROMPT_ERROR, str);
	if (error == ERR_INVALID)
		ft_dprintf(2, ERR_MSG_INVALID_IDENTIFIER, PROMPT_ERROR, str);
	if (error == ERR_NO_PERMISS)
		ft_dprintf(2, ERR_MSG_PERMISSION_DENIED, PROMPT_ERROR, str);
	if (error == ERR_IS_DIRECTORY)
		ft_dprintf(2, ERR_MSG_IS_A_DIRECTORY, PROMPT_ERROR, str);
	if (error == ERR_INVALID_OPTION)
		ft_dprintf(2, ERR_MSG_INVALID_OPTION, PROMPT_ERROR, str);
	if (error == ERR_HEREDOC_ABORTED)
		ft_dprintf(2, ERR_MSG_HEREDOC_EOF, PROMPT_WARNING, str);
	if (error == ERR_DQUOTE_ABORTED)
		ft_dprintf(2, ERR_MSG_UNEXPECTED_EOF, PROMPT_WARNING, str);
	sh_display_extended_errors(error, str);
}
