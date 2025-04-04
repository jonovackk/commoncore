




// sh_processor_pt.c

error_t sh_process_line(char **i_line, t_sh_env **env);

error_t sh_tokenize_input (t_sh_token **tokens, char *input_line, t_sh_env **environment);

error_t sh_execute_command_tree(t_sh_token **tokens, t_sh_node **execution_tree, t_sh_env **environment);

error_t   sh_process_heredoc(t_sh_node *execution_tree);

void sh_handle_prompt(t_sh_env **environment);


// sh_quote_pt.c

void sh_handle_prompt(t_sh_env **environment);

char *sh_get_dquote_line(char *line, char *tmp_file, int status);

int sh_get_dquote(char *line, t_sh_env **env, char *tmp);

error_t sh_quote_handler(char **line, t_sh_env **env, int status);


// sh_state_pt.c

char *sh_double_quote_state(char *addr, int type);

char *sh_heredoc_state (char *addr, int type);

t_sh_node *sh_command_tree_state(int reset, t_sh_node *root);

