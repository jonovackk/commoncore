/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_operators.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:06:24 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 12:23:28 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_OPERATORS_H
# define SH_OPERATORS_H

# include "sh_enumerates.h"
# include "sh_managers.h"

/* sh_closers_ops.c */
void		sh_close_multiple_fd(int count, int fd, ...);
void		sh_cmd_cleanup(t_sh_cmd *cmd);
void		sh_tree_fd_cleanup(t_sh_node *tree);
void		sh_exec_release(t_sh_exec *executor);
void		sh_cleanup_pipes(t_sh_pipe *pipes);

/* sh_cmd_ops.c */
char		**sh_tokenize_quoted(char *s, char *sep);
void		sh_refresh_args(t_sh_cmd *cmd);
void		sh_refresh_executable(t_sh_cmd *cmd);
t_error_t	sh_prepare_cmd(t_sh_cmd *cmd);
t_error_t	sh_traverse_heredocs(t_sh_node *node, int *hd);

/* sh_exec_cmd_ops.c */
void		sh_setup_input(t_sh_cmd *cmd, int last_hd);
void		sh_run_cmd(t_sh_cmd *cmd, int *node_fd, t_sh_exec *exec_ctx);
t_error_t	sh_init_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);
t_error_t	sh_check_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx);
void		sh_handle_command(t_sh_node *tree, int *node_fd,
				t_sh_exec *exec_ctx, t_exec_t mode);

/* sh_exec_handler_ops.c */
void		sh_execute_builtin_piped(int (*builtin_func)(t_sh_cmd *),
				t_sh_cmd *cmd, t_sh_exec *exec_ctx);
void		sh_validate_builtin_direct(int (*builtin_func)(t_sh_cmd *),
				t_sh_cmd *cmd, t_sh_exec *exec_ctx);
t_error_t	sh_validate_builtin_flags(t_sh_cmd *cmd);
t_error_t	sh_process_builtin(t_sh_cmd *cmd, int *fd, t_sh_exec *exec_ctx,
				t_exec_t mode);

/* sh_exec_utils.c */
void		sh_create_fake_pid_child(int err_code, t_sh_exec *executor);
void		sh_process_redirections(t_sh_cmd *cmd, int *node_fd);
void		sh_process_command_exit(int exit_status);
void		sh_fork_cleanup(t_sh_exec *executor);

/* Add any missing function declarations here */

/* sh_heredoc_ops.c */
void		sh_handle_heredoc_limit(t_sh_token *tokens, t_sh_env **environment);
void		sh_parse_heredoc_line(char **line, int fd, int expand);
int			sh_process_heredoc_line(char *delimiter, char *temp_file, int fd);
int			sh_handle_heredoc_exit(char *delimiter, char *temp_file,
				int exit_status);
int			sh_create_heredoc(char *delimiter, char *temp_file);

/* sh_logical_ops.c */
int			sh_wait_logical_operation(t_sh_exec *executor);
int			sh_execute_logical_and(t_sh_node *tree, int *node_fd,
				t_sh_exec *executor);
int			sh_execute_logical_or(t_sh_node *tree, int *node_fd,
				t_sh_exec *executor);

/* sh_mf_ops.c */
t_error_t	sh_heredoc_init(t_sh_cmd *cmd);
t_error_t	sh_line_expand(t_sh_cmd *cmd, char **file);
t_error_t	sh_heredoc_write(t_sh_cmd *cmd, char *file, int mode);
t_error_t	sh_output_load(t_sh_cmd *cmd);
t_error_t	sh_input_load(t_sh_cmd *cmd, int *hd_last);

/* sh_pipeline_ops.c */
void		sh_execute_command_multiplex(t_sh_node *node, int *node_fd,
				t_sh_exec *executor, t_exec_t execution_mode);
void		sh_wait_pipeline_processes(t_sh_pid *initial_pid,
				t_sh_exec *executor, t_exec_t execution_mode);
void		sh_execute_pipeline(t_sh_node *node, int *node_fd,
				t_sh_exec *executor, t_exec_t execution_mode);
void		sh_and_exec(t_sh_node *node, int *node_fd, t_sh_exec *ex,
				t_exec_t mode);
void		sh_or_exec(t_sh_node *node, int *node_fd, t_sh_exec *ex,
				t_exec_t mode);

/* sh_run_cmd_ops.c */

void	sh_setup_child_io(t_sh_cmd *cmd, int *node_fd);
void	sh_dup_input(t_sh_cmd *cmd, int *node_fd);
void	sh_dup_output(t_sh_cmd *cmd, int *node_fd);
void	sh_execute_child(t_sh_cmd *cmd, char **env_vars, t_sh_exec *exec_ctx);
void	sh_cleanup_parent(t_sh_cmd *cmd, int *node_fd);

/* sh_pipeline_aux.c */

void	sh_execute_pipeline_right_branch(t_sh_node *node, int *pipe_fd,
		t_sh_exec *executor);

#endif