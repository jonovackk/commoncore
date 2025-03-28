
#ifndef FT_ENUMERATES_H
# define FT_ENUMERATES_H



/**
 * @enum			e_quote_state
 * @brief			Quote state.
 */
typedef enum e_quote_state
{
	QT_NONE = 0,
	QT_SINGLE,
	QT_DOUBLE,
	QT_IGNORE
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
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
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
	FILE_HDOC = -3,
	FILE_HD,
	FILE_ERR,
	FILE_OK,
	FILE_UNK
} file_t;

/**
 *  @enum		handler_t
 *  @brief		Handler state.
 */
typedef enum handler_t
{
	HANDLER_IGN,
	HANDLER_INT,
	HANDLER_DQ,
	HANDLER_HD
} handler_t;

/**
 *  @enum		error_t
 *  @brief		Error return values.
 */

 typedef enum error_t
 {
	ERR_NONE,
	ERR_FAIL,
	ERR_GEN,
	ERR_NAN,
	ERR_ARGS,
	ERR_UNSET,
	ERR_NOENT,
	ERR_INV,
	ERR_HSTOP,
	ERR_DQSTOP,
	ERR_NOCMD,
	ERR_SYNTQ,
	ERR_SYNT,
	ERR_HLIM,
	ERR_NOPERM,
	ERR_DIR,
	ERR_OPT,
	ERR_FD,
	ERR_AMB
 } error_t;

#endif