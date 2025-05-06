#ifndef SH_MANAGERS_H
# define SH_MANAGERS_H

# define LEFT 0
# define RIGHT 1

# include <unistd.h>  /* For pid_t */
# include "sh_enumerates.h"

/* Forward declarations of basic structures */
typedef struct s_sh_token t_sh_token;
typedef struct s_sh_env_var t_sh_env;
typedef struct s_file_redirect t_sh_redir;
typedef struct s_sh_cmd t_sh_cmd;
typedef struct s_exec_node t_sh_node;
typedef struct s_process_id t_sh_pid;
typedef struct s_pipe_info t_sh_pipe;
typedef struct s_execution_context t_sh_exec;

/**
 * @brief Represents a single token in the shell's command line parsing
 * 
 * Tokens are the basic units of parsing, breaking down user input
 * into meaningful components like commands, arguments, and operators
 */
struct s_sh_token {
    char *content;           // Actual text of the token
    t_token_kind type;       // Classification (command, arg, redirect, etc.)
    struct s_sh_token *next;  // Next token in the sequence
    struct s_sh_token *prev;  // Previous token in the sequence
};

/**
 * @brief Represents an environment variable
 * 
 * Stores environment variables as a linked list, allowing 
 * dynamic management of shell environment
 */
struct s_sh_env_var {
    char *key;               // Name of the environment variable
    char **values;           // Possible multiple values for the variable
    struct s_sh_env_var *next;  // Next environment variable in the list
};

/**
 * @brief Manages input/output redirections for a command
 * 
 * Supports various redirection types like input, output, 
 * append, and here-document
 */
struct s_file_redirect {
    redir_t mode;    // Type of redirection (input, output, etc.)
    char *target;            // File to redirect to/from
    struct s_file_redirect *next;  // Next redirection in the list
};

/**
 * @brief Comprehensive description of a shell command
 * 
 * Encapsulates all information needed to execute a single command,
 * including file descriptors, arguments, and environment
 */
struct s_sh_cmd {
    int input_fd;            // Source of command input
    int output_fd;           // Destination of command output
    int heredoc_fd;          // File descriptor for here-document
    char *executable;        // Full path to the command executable
    char **arguments;        // Command-line arguments
    t_sh_redir *redirects;   // List of I/O redirections
    t_sh_env **environment;  // Reference to environment variables
};

/**
 * @brief Represents a node in the command execution tree
 * 
 * Supports complex command structures like pipelines and 
 * conditional execution through a binary tree representation
 */
struct s_exec_node {
    t_sh_cmd *cmd;       // Command to be executed at this node
    t_sh_token *token;       // Associated token (for operators)
    struct s_exec_node *left;   // Left subtree (typically first command)
    struct s_exec_node *right;  // Right subtree (next command/pipeline)
};

/**
 * @brief Manages process ID tracking for running commands
 * 
 * Implements a stack-like structure to track child processes
 * for management and waiting
 */
struct s_process_id {
    pid_t pid;               // Process Identifier
    struct s_process_id *next;  // Next process in the tracking list
};

/**
 * @brief Manages pipe file descriptors for command pipelines
 * 
 * Supports creating and tracking multiple pipe connections
 * between commands
 */
struct s_pipe_info {
    int fds[2];              // Read and write file descriptors
    struct s_pipe_info *next;  // Next pipe in the pipeline
};

/**
 * @brief Maintains the overall execution context of the shell
 * 
 * Centralizes management of active pipes and running processes
 * during command execution
 */
struct s_execution_context {
    t_sh_pipe *active_pipes; // Currently active pipe connections
    t_sh_pid *running_procs; // Processes currently being managed
};

/* Function prototypes */

/* sh_create_m.c */
t_sh_env    *sh_create_env_var(char *input);
t_sh_cmd    *sh_create_cmd(t_sh_redir *redirects, char **args, t_sh_env **env);
t_sh_node   *sh_create_exec_node(t_sh_cmd *cmd, t_sh_token *token);
t_sh_token  *sh_create_token(char **text, t_token_kind kind);

/* sh_cmd_m.c */
char        *sh_find_path(char *c, t_sh_env *env);
void        sh_free_cmd(t_sh_cmd *cmd);

/* sh_envvar_m.c */
void        sh_append_env(t_sh_env **env, t_sh_env *new);
void        sh_delete_env(t_sh_env **env, char *key);
void        sh_destroy_env_node(t_sh_env *env);
void        sh_destroy_env_list(t_sh_env *env);

/* sh_envvar_utils_m.c */
t_sh_env    *sh_find_env(t_sh_env *env, char *key);
t_sh_env    *sh_get_last_env(t_sh_env *env);
void        sh_update_env(t_sh_env **env, char *key, char *val);
void        sh_extend_env(t_sh_env **env, char *key, char *val);

/* sh_exec_m.c */
t_sh_exec   *sh_exec_init(void);

/* sh_node_m.c */
void    sh_set_parent_node(t_sh_node **root, t_sh_node *new_parent, int pos);
void    sh_set_child_node(t_sh_node **root, t_sh_node *child, int pos);
void    sh_connect_nodes(t_sh_node **root, t_sh_node *sibling, t_sh_cmd *cmd, t_sh_token *tok);
void    sh_destroy_node(t_sh_node *node);
void    sh_destroy_tree(t_sh_node *node);


/* sh_pid_m.c */
t_sh_pid    *sh_init_pid(pid_t id);
void        sh_pid_push(t_sh_pid **head, t_sh_pid *top);
t_sh_pid    *sh_pid_pop(t_sh_pid **head);
void        sh_delete_pid_list(t_sh_pid *pid_list);

/* sh_pipe_m.c */
t_sh_pipe   *sh_init_pipe(void);
void        sh_pipe_push(t_sh_pipe **head, t_sh_pipe *top);
t_sh_pipe   *sh_pipe_pop(t_sh_pipe **head);
void        sh_delete_pipe(t_sh_pipe *pipe_node);

/* sh_redir_m.c */
t_sh_redir  *sh_new_redir(t_sh_token *tok);
void        sh_add_redir(t_sh_redir **list, t_sh_redir *new_redir);
void        sh_clear_redir_list(t_sh_redir *redir);

/* sh_token_m.c */
void        sh_append_token(t_sh_token **list, t_sh_token *new_tok);
void        sh_delete_token(t_sh_token **list);
t_sh_token  *sh_clone_token(t_sh_token *tok);
void        sh_token_free(t_sh_token *tok);
void        sh_free_token_list(t_sh_token *list);

#endif