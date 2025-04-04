
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
	ERR_NONE, /*ERR_NOERRS*/
	ERR_FAIL_GENERAL, /*ERR_FAILED*/
	ERR_NO_COMMAND, /*ERR_ERRORS*/
	ERR_NOT_A_NUMBER, /*ERR_NOTNUM*/
	ERR_TOO_MANY_ARGS, /*ERR_TMARGS*/
	ERR_VAR_UNSET, /* ERR_NOTSET*/
	ERR_NO_ENTRY, /*ERR_NOFORD*/
	ERR_INVALID, /*ERR_NOTVAL*/
	ERR_HEREDOC_ABORTED, /*ERR_HDSTOP*/
	ERR_DQUOTE_ABORTED, /*ERR_DQSTOP*/
	ERR_NO_COMMAND, /*ERR_NOTCMD*/
	ERR_BAD_QUOTE, /*ERR_SYNTXQ*/
	ERR_SYNTAX, /*ERR_SYNTXT*/
	ERR_HEREDOC_LIMIT, /*ERR_HLIMIT*/
	ERR_NO_PERMISS, /*ERR_NOPERM*/
	ERR_IS_DIRECTORY, /*ERR_ISADIR*/
	ERR_INVALID_OPTION, /*ERR_INVOPT*/
	ERR_FD_LIMIT, /*ERR_INVFDS*/
	ERR_AMBIGUOUS_REDIRECT /*ERR_AMBRED*/
 } error_t;

#endif