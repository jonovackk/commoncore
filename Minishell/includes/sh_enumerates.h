/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_enumerates.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:06:24 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 15:06:24 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENUMERATES_H
# define SH_ENUMERATES_H

/* Quote state enumeration */
typedef enum e_quote_state
{
	QUOTE_NONE = 0,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_IGNORE
}	t_quote_state;

/* Token kind enumeration */
typedef enum e_token_kind
{
	TOKEN_TEXT = 0b00001,
	TOKEN_PARENTHESIS = 0b00010,
	TOKEN_LOGICAL = 0b00100,
	TOKEN_PIPE = 0b01000,
	TOKEN_REDIRECT = 0b10000
}	t_token_kind;

/* Redirection type enumeration */
typedef enum e_redir_t
{
	REDIR_INPUT,
	REDIR_HEREDOC,
	REDIR_OUTPUT,
	REDIR_APPEND
}	t_redir_t;

/* Execution state enumeration */
typedef enum e_exec_t
{
	EXEC_WAIT = 0,
	EXEC_PIPE = 1
}	t_exec_t;

/* File type enumeration */
typedef enum e_file_t
{
	FILE_HEREDOC_TEMP = -3,
	FILE_HEREDOC,
	FILE_ERROR,
	FILE_READY,
	FILE_UNKNOWN
}	t_file_t;

/* Command handler type enumeration */
typedef enum e_handler_t
{
	HANDLER_IGN,
	HANDLER_INTERRUPT,
	HANDLER_DQUOTE,
	HANDLER_HEREDOC
}	t_handler_t;

/* Error type enumeration */
typedef enum e_error_t
{
	ERR_NONE,
	ERR_FAIL_GENERAL,
	ERR_ERRORS,
	ERR_NOT_A_NUMBER,
	ERR_TOO_MANY_ARGS,
	ERR_VAR_UNSET,
	ERR_NO_ENTRY,
	ERR_INVALID,
	ERR_HEREDOC_ABORTED,
	ERR_DQUOTE_ABORTED,
	ERR_NO_COMMAND,
	ERR_BAD_QUOTE,
	ERR_SYNTAX,
	ERR_HEREDOC_LIMIT,
	ERR_NO_PERMISS,
	ERR_IS_DIRECTORY,
	ERR_INVALID_OPTION,
	ERR_FD_LIMIT,
	ERR_AMBIGUOUS_REDIRECT
}	t_error_t;

#endif