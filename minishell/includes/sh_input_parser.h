#ifndef SH_INPUT_PARSER_H
# define SH_INPUT_PARSER_H

/* sh_input_tokenizer.c */

int sh_is_shell_operator(char *input, t_qstate qstat);

t_token_kind sh_classify_token(char *input, t_qstate qstat);

t_sh_token *sh_tokenize_input(char *input, t_qstate qstat);

int sh_contains_unquoted_wildcard(char *input, t_qstate qstat);

void sh_expand_tilde(t_sh_token **token_list, t_envvar *home_var);

/* sh_psng_help.c */

int sh_update_quote_state(char c, t_qstate *qstatus);

int sh_ignoring_quotes(char *str);

void sh_rmv_inv_parentheses(t_sh_token **tokens);

/* sh_quote_procs.c */

void sh_handle_unclosed_quotes(char **line, int tmp_fd, t_qstate state);

t_qstate sh_detect_quotes(char *line, char *end_marker, t_qstate state);

void sh_rmv_quotes(char **line, t_qstate state);

/* sh_token_valid.c */

int sh_validate_subtoken(t_sh_token *token);

int sh_validate_syntax(t_sh_token *token, char **err_token);

int sh_check_parenthesis_balance(t_sh_token *tokens);

int sh_validate_tokens(t_sh_token *tokens, char **err_token);

int sh_check_ops_in_brackets(t_sh_token *token);

/* sh_tree_build.c */


/* sh_var_expand.c */

int sh_get_env_var_length(char *str);

void sh_process_quoted_section(char **s, int *rem, t_qstate *state);

void sh_insert_env_vars(t_sh_env *env, char *s, char ***res_parts, t_qstate state);

void sh_replace_env_vars(t_sh_env *env, char **line, t_qstate state);


/* sh_wildcard_matcher.c */

int sh_match_wildcard(const char *filename, const char *pattern);

char **sh_get_matching_files(char *pattern);

void sh_expd_wildcard_token(t_sh_token **token_list, t_sh_token **current);

char *sh_format_wildcard_matches(char ***file_array);

void sh_replace_wildcards(char **str);




#endif

