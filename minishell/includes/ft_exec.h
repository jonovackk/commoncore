#ifndef FT_EXECUTION_H
# define FT_EXECUTION_H


void    setup_input(t_sh_cmd *cmd, int last_hd);

void    run_cmd(t_sh_cmd *cmd, int *node_fd, t_sh_exec *exec_ctx);

error_t     init_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);

error_t     check_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);

void        handle_command(t_sh_node *tree, int *node_fd, t_sh_exec *exec_ctx, exec_t mode);

error_t     open_heredocs(t_sh_cmd *cmd);

error_t     check_file(t_sh_cmd *cmd, char **file);

error_t     open_file_fd(t_sh_cmd *cmd, char *file, int mode);

error_t     open_outputs(t_sh_cmd *cmd);

error_t     open_inputs(t_sh_cmd *cmd, int *hd_last);

void    pipe_builtin(int(*builtin_func)(t_sh_cmd *), t_sh_cmd *cmd, t_sh_exec *exec_ctx);

void    wait_builtin(int (*builtin_func)(t_sh_cmd *), t_sh_cmd, t_sh_exec *exec_ctx);

error_t     builtin_checker(t_sh_cmd *cmd);

error_t     execute_builtin(t_sh_cmd *cmd, int *fd, t_sh_exec *exec_ctx, exec_t mode);

char    **quoted_split(char *s, char *sep);

void    update_arguments(t_sh_cmd *cmd);

void    update_command_path(t_sh_cmd *cmd);

error_t     prepare_command(t_sh_cmd *cmd);

error_t     handle_heredocs(t_sh_node *nd, int *nd, int *hd);


