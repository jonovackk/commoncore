#ifndef SH_INPUT_PARSER_H
# define SH_INPUT_PARSER_H

# include "sh_enumerates.h"
# include "sh_managers.h"

/* sh_input_tokenizer.c */
int sh_is_shell_operator(char *input, t_quote_state qstat);
t_token_kind sh_classify_token(char **input, t_quote_state qstat);
t_sh_token *sh_tokenizer_input(char *input, t_quote_state qstat);
int sh_contains_unquoted_wildcard(char *input, t_quote_state qstat);
void sh_expand_tilde(t_sh_token **token_list, t_sh_env *home_var);

/* sh_psng_help.c */
int sh_update_quote_state(char c, t_quote_state *qstatus);
int sh_ignoring_quotes(char *str);
void sh_rmv_inv_parentheses(t_sh_token **tokens);

/* sh_quote_procs.c */
void sh_handle_unclosed_quotes(char **line, int tmp_fd, t_quote_state state);
t_quote_state sh_detect_quotes(char *line, char *end_marker, t_quote_state state);
void sh_rmv_quotes(char **line, t_quote_state state);

/* sh_token_valid.c */
int sh_validate_subtoken(t_sh_token *token);
int sh_validate_syntax(t_sh_token *token, char **err_token);
int sh_check_parenthesis_balance(t_sh_token *tokens);
int sh_validate_tokens(t_sh_token *tokens, char **err_token);
int sh_check_ops_in_brackets(t_sh_token *token);

/* sh_tree_build.c */
t_sh_node *sh_cmd_token(t_sh_token **tokens, t_sh_env **env, t_sh_token *tmp);
void sh_brace_tree(t_sh_token **tk, t_sh_node **tree, t_sh_env **env);
void sh_connect_ops(t_sh_token **tk, t_sh_node **tree, t_sh_env **env);
t_sh_node *sh_build_tree(t_sh_token *tokens, t_sh_env **env);

/* sh_var_expand.c */
int sh_get_env_var_length(char *str);
void sh_process_quoted_section(char **s, int *rem, t_quote_state *state);
void sh_insert_env_vars(t_sh_env *env, char *s, char ***res_parts, t_quote_state state);
void sh_replace_env_vars(t_sh_env *env, char **line, t_quote_state state);

/* sh_wildcard_matcher.c */
int sh_match_wildcard(const char *filename, const char *pattern);
char **sh_get_matching_files(char *pattern);
void sh_expd_wildcard_token(t_sh_token **token_list, t_sh_token **current);
char *sh_format_wildcard_matches(char ***file_array);
void sh_replace_wildcards(char **str);

#endif