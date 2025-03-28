#ifndef FT_EXECUTION_H
# define FT_EXECUTION_H


void    sh_setup_input(t_sh_cmd *cmd, int last_hd);

void    sh_run_cmd(t_sh_cmd *cmd, int *node_fd, t_sh_exec *exec_ctx);

error_t     sh_init_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);

error_t     sh_check_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);

void        sh_handle_command(t_sh_node *tree, int *node_fd, t_sh_exec *exec_ctx, exec_t mode);

error_t     sh_heredoc_init(t_sh_cmd *cmd);

error_t     sh_line_expand(t_sh_cmd *cmd, char **file);

error_t     sh_heredoc_write(t_sh_cmd *cmd, char *file, int mode);

error_t     sh_output_load(t_sh_cmd *cmd);

error_t     sh_input_load(t_sh_cmd *cmd, int *hd_last);

void    sh_setup_input(t_sh_cmd *cmd, int last_hd);

void    sh_run_cmd(t_sh_cmd *cmd, int *node_fd, t_sh_exec *exec_ctx);

error_t     sh_init_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);

error_t     sh_check_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);

char    **sh_tokenize_quoted(char *s, char *sep);

void    sh_refresh_args(t_sh_cmd *cmd);

void	sh_refresh_executable(t_sh_cmd *cmd);

error_t     sh_prepare_cmd(t_sh_cmd *cmd);

error_t     sh_traverse_heredocs(t_sh_node *nd, int *nd, int *hd);

void sh_tree_fd_cleanup(t_sh_token *tree);

void sh_cmd_cleanup(t_sh_cmd *cmd);

void sh_close_multiple_fd(int count, int fd, ...);

void sh_exec_release(t_sh_exec *executor);

void sh_cleanup_pipes(t_sh_pipe *pipes);

void    sh_execute_builtin_piped(int(*builtin_func)(t_sh_cmd *), t_sh_cmd *cmd, t_sh_exec *exec_ctx);

void    sh_validate_builtin_direct(int (*builtin_func)(t_sh_cmd *), t_sh_cmd, t_sh_exec *exec_ctx);

error_t     sh_validate_builtin_flags(t_sh_cmd *cmd);

error_t     sh_process_builtin(t_sh_cmd *cmd, int *fd, t_sh_exec *exec_ctx, exec_t mode);

void sh_handle_heredoc_limit(t_sh_token *tokens, t_sh_env **environment);

void sh_parse_heredoc_line(char **line, int fd, int expand);

int sh_process_heredoc_line(char *delimiter, char *temp_file, int fd);

int sh_handle_heredoc_exit(char *delimiter, char *temp_file, int exit_status);

void sh_execute_command_multiplex(t_sh_node *tree, int *node_fd, 
    t_sh_exec *executor, t_execution_mode execution_mode);

void sh_wait_pipeline_processes(t_sh_pid *initial_pid, t_sh_exec *executor, 
        t_execution_mode execution_mode);
         
void sh_execute_pipeline(t_sh_node *tree, int *node_fd, t_sh_exec *executor, 
        t_execution_mode execution_mode);
          
void	sh_and_exec(t_sh_node *tree, int *node_fd, t_sh_exec *ex, exec_t mode);

void	sh_or_exec(t_sh_node *tree, int *node_fd, t_sh_exec *ex, exec_t mode);
