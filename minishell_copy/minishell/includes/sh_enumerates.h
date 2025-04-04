
#ifndef FT_ENUMERATES_H
# define FT_ENUMERATES_H



/**
 * @enum			e_quote_state
 * @brief			Quote state.
 */
typedef enum e_quote_state
{
	QUOTE_NONE = 0,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_IGNORE
}	t_qstate;


/**
 * @enum			e_token_type
 * @brief			Token type.
 */
typedef enum e_token_kind
{
	TOKEN_TEXT = 0b00001, //TK_STRING
	TOKEN_PARENTHESIS = 0b00010, //TK_BRACES
	TOKEN_LOGICAL = 0b00100, //TK_BINOPS
	TOKEN_PIPE = 0b01000, //TK_PIPEXS
	TOKEN_REDIRECT = 0b10000 //TK_REDIRS
}	t_token_kind;

/**
 *  @enum		redir_t
 *  @brief		Redirection type.
 */
typedef enum redir_t
{
	REDIR_INPUT,
	REDIR_HEREDOC,
	REDIR_OUTPUT,
	REDIR_APPEND
} redir_t;

/**
 *  @enum		exec_t
 *  @brief		Execution mode.
 */
typedef enum exec_t
{
	EXEC_WAIT = 0,
	EXEC_PIPE = 1
} exec_t;

/**
 *  @enum		file_t
 *  @brief		File opening status.
 */
typedef enum file_t
{
	FILE_HEREDOC_TEMP = -3,
	FILE_HEREDOC,
	FILE_ERROR,
	FILE_READY,
	FILE_UNKNOWN
} file_t;

/**
 *  @enum		handler_t
 *  @brief		Handler state.
 */
typedef enum handler_t
{
	HANDLER_IGN,
	HANDLER_INTERRUPT,
	HANDLER_DQUOTE,
	HANDLER_HEREDOC
} handler_t;

/**
 *  @enum		error_t
 *  @brief		Error return values.
 */

 typedef enum error_t
 {
	ERR_NONE,
	ERR_FAIL_GENERAL,
	ERR_FAIL_UNKNOWN,
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
 } error_t;

#endif