/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_managers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:06:24 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 15:06:24 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_MANAGERS_H
# define SH_MANAGERS_H

# define LEFT 0
# define RIGHT 1

# include "sh_enumerates.h"
# include <unistd.h>

typedef struct s_sh_token			t_sh_token;
typedef struct s_sh_env_var			t_sh_env;
typedef struct s_file_redirect		t_sh_redir;
typedef struct s_sh_cmd				t_sh_cmd;
typedef struct s_exec_node			t_sh_node;
typedef struct s_process_id			t_sh_pid;
typedef struct s_pipe_info			t_sh_pipe;
typedef struct s_execution_context	t_sh_exec;

struct							s_sh_token
{
	char				*content;
	t_token_kind		type;
	struct s_sh_token	*next;
	struct s_sh_token	*prev;
};

struct							s_sh_env_var
{
	char				*key;
	char				**values;
	struct s_sh_env_var	*next;
};

struct							s_file_redirect
{
	redir_t					mode;
	char					*target;
	struct s_file_redirect	*next;
};

struct							s_sh_cmd
{
	int				input_fd;
	int				output_fd;
	int				heredoc_fd;
	char			*executable;
	char			**arguments;
	t_sh_redir		*redirects;
	t_sh_env		**environment;
};

struct							s_exec_node
{
	t_sh_cmd			*cmd;
	t_sh_token			*token;
	struct s_exec_node	*left;
	struct s_exec_node	*right;
};

struct							s_process_id
{
	pid_t				pid;
	struct s_process_id	*next;
};

struct							s_pipe_info
{
	int					fds[2];
	struct s_pipe_info	*next;
};

struct							s_execution_context
{
	t_sh_pipe		*active_pipes;
	t_sh_pid		*running_procs;
};

t_sh_env		*sh_create_env_var(char *input);
t_sh_cmd		*sh_create_cmd(t_sh_redir *redirects,
					char **args,
					t_sh_env **env);
t_sh_node		*sh_create_exec_node(t_sh_cmd *cmd, t_sh_token *token);
t_sh_token		*sh_create_token(char **text, t_token_kind kind);

char			*sh_find_path(char *c, t_sh_env *env);
void			sh_free_cmd(t_sh_cmd *cmd);

void			sh_append_env(t_sh_env **env, t_sh_env *new);
void			sh_delete_env(t_sh_env **env, char *key);
void			sh_destroy_env_node(t_sh_env *env);
void			sh_destroy_env_list(t_sh_env *env);

t_sh_env		*sh_find_env(t_sh_env *env, char *key);
t_sh_env		*sh_get_last_env(t_sh_env *env);
void			sh_update_env(t_sh_env **env, char *key, char *val);
void			sh_extend_env(t_sh_env **env, char *key, char *val);

t_sh_exec		*sh_exec_init(void);

void			sh_set_parent_node(t_sh_node **root,
					t_sh_node *new_parent,
					int pos);
void			sh_set_child_node(t_sh_node **root,
					t_sh_node *child,
					int pos);
void			sh_connect_nodes(t_sh_node **root,
					t_sh_node *sibling,
					t_sh_cmd *cmd,
					t_sh_token *tok);
void			sh_destroy_node(t_sh_node *node);
void			sh_destroy_tree(t_sh_node *node);

t_sh_pid		*sh_init_pid(pid_t id);
void			sh_pid_push(t_sh_pid **head, t_sh_pid *top);
t_sh_pid		*sh_pid_pop(t_sh_pid **head);
void			sh_delete_pid_list(t_sh_pid *pid_list);

t_sh_pipe		*sh_init_pipe(void);
void			sh_pipe_push(t_sh_pipe **head, t_sh_pipe *top);
t_sh_pipe		*sh_pipe_pop(t_sh_pipe **head);
void			sh_delete_pipe(t_sh_pipe *pipe_node);

t_sh_redir		*sh_new_redir(t_sh_token *tok);
void			sh_add_redir(t_sh_redir **list, t_sh_redir *new_redir);
void			sh_clear_redir_list(t_sh_redir *redir);

void			sh_append_token(t_sh_token **list, t_sh_token *new_tok);
void			sh_delete_token(t_sh_token **list);
t_sh_token		*sh_clone_token(t_sh_token *tok);
void			sh_token_free(t_sh_token *tok);
void			sh_free_token_list(t_sh_token *list);

#endif
