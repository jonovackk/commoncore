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
 * @brief Manages input/output redirections for a command
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
    t_sh_cmd *command;       // Command to be executed at this node
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