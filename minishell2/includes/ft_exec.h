#ifndef FT_EXECUTION_H
# define FT_EXECUTION_H


void    setup_input(t_sh_cmd *cmd, int last_hd);

void    run_cmd(t_sh_cmd *cmd, int *node_fd, t_sh_exec *exec_ctx);

error_t     init_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);

error_t     check_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);

void        handle_command(t_sh_node *tree, int *node_fd, t_sh_exec *exec_ctx, exec_t mode);