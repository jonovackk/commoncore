
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
#endif