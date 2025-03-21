#ifndef FT_PARSING_H
# define FT_PARSING_H

# include "ft_dt_struct.h"

/**
 * @brief            Quote state updater.
 * 
 * @param c          Current character.
 * @param qstatus    Current quote state address.
 * 
 * @return           1 if quote state changed, 0 otherwise.
*/
int            update_quote_status(char c, t_qstate *qstatus);

/**
 * @brief            Tokenize a string.
 * 
 * @param input      String to tokenize.
 * @param qstat      Quote state.
 * 
 * @return           t_token linked list.
*/
t_sh_token        *parse_into_tokens(char *input, t_qstate qstat);

/**
 * @brief            Check if a string starts by a token.
 * 
 * @param input      String to analyze.
 * @param qstat      Carried quote state.
 * 
 * @return           1 if the string is headed by a token, 0 otherwise.
*/
int            is_valid_operator(char *input, t_qstate qstat);

/**
 * @brief            Get token type from string.
 * 
 * @param input      String to analyze.
 * @param qstat      Carried quote state.
 * 
 * @return           Token type enumeration value.
*/
t_token_kind   get_token_category(char *input, t_qstate qstat);

/**
 * @brief            Check if a brace group contains a binary operator.
 * 
 * @param token      Token linked list.
 * 
 * @return           1 in case of valid group, 0 otherwise.
*/
int            check_valid_logical_parenthesis(t_sh_token *token);

/**
 * @brief            Update linked list, deleting useless brace tokens.
 * 
 * @param tokens     Linked list.
*/
void           clean_parenthesis_tokens(t_sh_token **tokens);

/**
 * @brief            Verify if a string is a wildcard string.
 * 
 * @param input      String to check.
 * @param qstat      Quote state.
 * 
 * @return           1 if the string contains only *, 0 otherwise.
*/
int            check_for_wildcard(char *input, t_qstate qstat);

/**
 * @brief            Format tokens (wildcard && quotes).
 * 
 * @param token_list Token linked list address.
 * @param home_var   HOME t_envvar pointer.
*/
void           process_home_expansion(t_sh_token **token_list, t_sh_env *home_var);

/**
 * @brief            Unquoted string len.
 * 
 * @param str        String.
 * 
 * @return           Unquoted len of the string.
*/
int            count_chars_without_quotes(char *str);


/**
 * @brief			Check for syntax error.
 * 
 * @param str		String to check.
 * @param end		String ending.
 * @param qs		Quote_state.
 * 
 * @return			Syntax error char.		
*/
t_qstate    quote_error(char *line, char *end_marker, t_qstate state);

void    process_wildcard_token(t_sh_token **token_list, t_sh_token **current);

char    **wildcard_files(char *pattern);

int     match_wildcard(const char *fname, const char *pattern);

int     check_subtoken_validity(t_sh_token *token);

int     validate_token_sequence(t_sh_token *token, char **err_token);

int     check_bracket_balance(t_sh_token *tokens);

int     verify_tokens(t_sh_token *tokens, char **err_token);

int     validate_binop_in_brackets(t_sh_token *token);

void enforce_quotes(char **line, int tmp_fd, t_qstate state);

void remove_quotes(char **line, t_qstate state);

int     calc_var_length(char *str);

void    skip_quotes(char **s, int *rem, t_qstate *state);

void    insert_env_variable(t_sh_env *env, char *s, char ***res_parts, t_qstate state);

void     replace_env_vars(t_sh_env *env, char **line, t_qstate state);




#endif