#ifndef FT_MANAGERS_H
# define FT_MANAGERS_H

# define LEFT 0
# define RIGHT 1

/**
 * @brief Represents a single token in the shell's command line parsing
 * 
 * Tokens are the basic units of parsing, breaking down user input
 * into meaningful components like commands, arguments, and operators
 */
typedef struct s_shell_token {
    char *content;           // Actual text of the token
    t_token_kind type;       // Classification (command, arg, redirect, etc.)
    struct s_shell_token *next;  // Next token in the sequence
    struct s_shell_token *prev;  // Previous token in the sequence
} t_sh_token;

/**
 * @brief Represents an environment variable
 * 
 * Stores environment variables as a linked list, allowing 
 * dynamic management of shell environment
 */
typedef struct s_env_var {
    char *key;               // Name of the environment variable
    char **values;           // Possible multiple values for the variable
    struct s_env_var *next;  // Next environment variable in the list
} t_sh_env;

/**
 * @brief Manages input/output redirections for a commandsh_init_pipes
 * 
 * Supports various redirection types like input, output, 
 * append, and here-document
 */
typedef struct s_file_redirect {
    t_redirect_type mode;    // Type of redirection (input, output, etc.)
    char *target;            // File to redirect to/from
    struct s_file_redirect *next;  // Next redirection in the list
} t_sh_redir;

/**
 * @brief Comprehensive description of a shell command
 * 
 * Encapsulates all information needed to execute a single command,
 * including file descriptors, arguments, and environment
 */
typedef struct s_cmd_detail {
    int input_fd;            // Source of command input
    int output_fd;           // Destination of command output
    int heredoc_fd;          // File descriptor for here-document
    char *executable;        // Full path to the command executable
    char **arguments;        // Command-line arguments
    t_sh_redir *redirects;   // List of I/O redirections
    t_sh_env **environment;  // Reference to environment variables
} t_sh_cmd;

/**
 * @brief Represents a node in the command execution tree
 * 
 * Supports complex command structures like pipelines and 
 * conditional execution through a binary tree representation
 */
typedef struct s_exec_node {
    t_sh_cmd *cmd;       // Command to be executed at this node
    t_sh_token *token;       // Associated token (for operators)
    struct s_exec_node *left;   // Left subtree (typically first command)
    struct s_exec_node *right;  // Right subtree (next command/pipeline)
} t_sh_node;

/**
 * @brief Manages process ID tracking for running commands
 * 
 * Implements a stack-like structure to track child processes
 * for management and waiting
 */
typedef struct s_process_id {
    pid_t pid;               // Process Identifier
    struct s_process_id *next;  // Next process in the tracking list
} t_sh_pid;

/**
 * @brief Manages pipe file descriptors for command pipelines
 * 
 * Supports creating and tracking multiple pipe connections
 * between commands
 */
typedef struct s_pipe_info {
    int fds[2];              // Read and write file descriptors
    struct s_pipe_info *next;  // Next pipe in the pipeline
} t_sh_pipe;

/**
 * @brief Maintains the overall execution context of the shell
 * 
 * Centralizes management of active pipes and running processes
 * during command execution
 */
typedef struct s_execution_context {
    t_sh_pipe *active_pipes; // Currently active pipe connections
    t_sh_pid *running_procs; // Processes currently being managed
} t_sh_exec;



// sh_create_m.c

/**
 * @brief            Creates a new environment variable.
 * 
 * @param input      Raw string value.
 * 
 * @return           A pointer to the newly allocated environment variable.
 */
t_sh_env    *sh_create_env_var(char *input);

/**
 * @brief            Creates a new command structure.
 * 
 * @param redirects  Redirections linked list.
 * @param args       Arguments string array.
 * @param env        Environment variables linked list.
 * 
 * @return           A pointer to the newly allocated command structure.
 */
t_sh_cmd    *sh_create_cmd(t_sh_redir *redirects, char **args, t_sh_env **env);

/**
 * @brief            Creates a new execution node.
 * 
 * @param cmd        Command pointer.
 * @param token      Token pointer.
 * 
 * @return           A pointer to the newly allocated execution node.
 */
t_sh_node   *sh_create_exec_node(t_sh_cmd *cmd, t_sh_token *token);

/**
 * @brief            Creates a new token.
 * 
 * @param text       Text value of the token.
 * @param kind       Token identifier (see enum).
 * 
 * @return           A pointer to the newly allocated token.
 */
t_sh_token  *sh_create_token(char **text, t_token_kind kind);



// sh_cmd_m.c

/**
 * @brief            Retrieves the command path from the environment.
 * 
 * @param c          Command string.
 * @param env        Environment linked list.
 * 
 * @return           Command path.
 */
char        *sh_find_path(char *c, t_sh_env *env);

/**
 * @brief            De-allocate a command structure.
 * 
 * @param cmd        Command to free.
 */
void    sh_free_cmd(t_sh_cmd *cmd);

//sh_envvar_m.c

/**
 * @brief            Adds an environment variable to the linked list.
 * 
 * @param env        Environment linked list.
 * @param new        New environment variable to add.
 */
void    sh_append_env(t_sh_env **env, t_sh_env *new);

/**
 * @brief            Removes an environment variable from the list.
 * 
 * @param env        Environment linked list.
 * @param key        Name of the variable to remove.
 */
void    sh_delete_env(t_sh_env **env, char *key);

/**
 * @brief            De-allocate a single environment variable.
 * 
 * @param env        Environment variable to free.
 */
void    sh_destroy_env_node(t_sh_env *env);

/**
 * @brief            De-allocate the entire environment linked list.
 * 
 * @param env        Environment linked list to free.
 */
void    sh_destroy_env_list(t_sh_env *env);


//sh_envvar_utils_m.c

/**
 * @brief            Retrieves an environment variable by name.
 * 
 * @param env        Environment linked list.
 * @param key        Name of the variable to search for.
 * 
 * @return           Pointer to the found environment variable, NULL otherwise.
 */
t_sh_env    *sh_find_env(t_sh_env *env, char *key);

/**
 * @brief            Retrieves the last environment variable in the list.
 * 
 * @param env        Environment linked list.
 * 
 * @return           Pointer to the last environment variable.
 */
t_sh_env    *sh_get_last_env(t_sh_env *env);

/**
 * @brief            Sets the value of an environment variable.
 * 
 * @param env        Environment linked list.
 * @param key        Name of the variable to modify.
 * @param val        New value for the variable.
 */
void    sh_update_env(t_sh_env **env, char *key, char *val);

/**
 * @brief            Appends a string to an environment variable value.
 * 
 * @param env        Environment linked list.
 * @param key        Name of the variable.
 * @param val        String to append.
 */
void    sh_extend_env(t_sh_env **env, char *key, char *val);



//sh_exec_m.c

/**
 * @brief            Initializes an execution structure.
 * 
 * @return           A pointer to the newly allocated execution structure.
 */
t_sh_exec   *sh_exec_init(void);



//sh_pid_m.c
/**
 * @brief            Creates a new process ID structure.
 * 
 * @param id         Process ID.
 * 
 * @return           A pointer to the newly allocated PID structure.
 */
t_sh_pid    *sh_init_pid(pid_t id);

/**
 * @brief            Pushes a PID into a stack.
 * 
 * @param list       PID stack.
 * @param proc       Process ID structure to push.
 */
void        sh_pid_push(t_sh_pid **head, t_sh_pid *top);

/**
 * @brief            Pops a PID from the stack.
 * 
 * @param list       PID stack.
 * 
 * @return           Pointer to the popped PID structure.
 */
t_sh_pid    *sh_pid_pop(t_sh_pid **head);

/**
 * @brief            De-allocate the entire PID stack.
 * 
 * @param list       PID stack to free.
 */
void  sh_delete_pid_list(t_sh_pid *pid_list);



//sh_pipe_m.c

/**
 * @brief            Creates a new pipe structure.
 * 
 * @return           A pointer to the newly allocated pipe structure.
 */
t_sh_pipe   *sh_init_pipe(void);

/**
 * @brief            Pushes a pipe into a stack.
 * 
 * @param list       Pipe stack.
 * @param pipe_obj   Pipe structure to push.
 */
void  sh_pipe_push(t_sh_pipe **head, t_sh_pipe *top);

/**
 * @brief            Pops a pipe from the stack.
 * 
 * @param list       Pipe stack.
 * 
 * @return           Pointer to the popped pipe structure.
 */
t_sh_pipe   *sh_pipe_pop(t_sh_pipe **head);

/**
 * @brief            De-allocate a pipe structure.
 * 
 * @param p          Pipe structure to free.
 */
void  sh_delete_pipe(t_sh_pipe *pipe_node);



//sh_redir_m.c
/**
 * @brief            Creates a new redirection structure.
 * 
 * @param tok        Token representing the redirection.
 * 
 * @return           A pointer to the newly allocated redirection structure.
 */
t_sh_redir  *sh_new_redir(t_sh_token *tok);

/**
 * @brief            Adds a redirection to the linked list.
 * 
 * @param list       Redirection linked list.
 * @param new_redir  Redirection to append.
 */
void  sh_add_redir(t_sh_redir **list, t_sh_redir *new_redir);


/**
 * @brief            De-allocate a redirection list.
 * 
 * @param redir      Redirection list to free.
 */
void  sh_clear_redir_list(t_sh_redir *redir);



//sh_token_m.c
/**
 * @brief            Adds a token to the linked list.
 * 
 * @param list       Token linked list.
 * @param new_tok    New token to append.
 */
void      sh_append_token(t_sh_token **list, t_sh_token *new_tok);

/**
 * @brief            Removes a token from the linked list.
 * 
 * @param list       Token linked list.
 */
void      sh_delete_token(t_sh_token **list);

/**
 * @brief            Duplicates a token.
 * 
 * @param tok        Token to duplicate.
 * 
 * @return           A pointer to a new token with the same properties.
 */
t_sh_token  *sh_clone_token(t_sh_token *tok);

/**
 * @brief            De-allocate a token.
 * 
 * @param tok        Token to free.
 */
void      sh_token_free(t_sh_token *tok);

/**
 * @brief            De-allocate the entire token linked list.
 * 
 * @param list       Token linked list to free.
 */
void      sh_free_token_list(t_sh_token *list);


#endif