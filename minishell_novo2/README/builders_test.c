/**
 * @brief Creates and initializes a new environment variable structure
 * 
 * Parses the input string to extract variable name and values,
 * handling the format "NAME=VALUE1:VALUE2:..."
 * 
 * @param value String containing environment variable definition
 * @return Pointer to new environment variable structure, NULL if allocation fails
 */
t_sh_env *create_env_variable(char *value)
{
    t_sh_env *new_var;
    char *equal_sign;
    char **temp_array;
    
    // Allocate memory for the new environment variable structure
    new_var = malloc(sizeof(t_sh_env));
    if (!new_var)
        return (NULL);
    
    // Find the equals sign that separates key from values
    equal_sign = ft_strchr(value, '=');
    if (equal_sign)
    {
        // Split the string to get the key
        temp_array = ft_split(value, '=');
        new_var->key = ft_strdup(temp_array[0]);
        ft_free_tab((void **)temp_array);
        
        // Split the values portion by colons
        new_var->values = ft_split(equal_sign + 1, ':');
    }
    else
    {
        // If there's no equals sign, the whole string is the key with no values
        new_var->key = ft_strdup(value);
        new_var->values = NULL;
    }
    
    // Initialize the next pointer to NULL
    new_var->next = NULL;
    return (new_var);
}

/**
 * @brief Creates and initializes a new file redirection structure
 * 
 * @param mode Type of redirection (input, output, append, etc.)
 * @param target Filename or path for the redirection
 * @return Pointer to new redirection structure, NULL if allocation fails
 */
t_sh_redir *create_redirection(t_redirect_type mode, char *target)
{
    t_sh_redir *new_redir;
    
    // Allocate memory for the new redirection structure
    new_redir = malloc(sizeof(t_sh_redir));
    if (!new_redir)
        return (NULL);
    
    // Initialize redirection properties
    new_redir->mode = mode;
    new_redir->target = ft_strdup(target);
    new_redir->next = NULL;
    
    return (new_redir);
}

/**
 * @brief Creates and initializes a new command structure
 * 
 * Sets up a command with its redirections, arguments and environment
 * 
 * @param redirects Linked list of redirections for this command
 * @param args Array of command arguments (including the command itself)
 * @param environment Pointer to environment variables collection
 * @return Pointer to new command structure, NULL if allocation fails
 */
t_sh_cmd *create_command(t_sh_redir *redirects, char **args, t_sh_env **environment)
{
    t_sh_cmd *new_command;
    
    // Allocate memory for the new command structure
    new_command = malloc(sizeof(t_sh_cmd));
    if (!new_command)
        return (NULL);
    
    // Initialize command properties with default values
    new_command->input_fd = 0;         // Default to standard input
    new_command->output_fd = 1;        // Default to standard output
    new_command->heredoc_fd = -1;      // Indicate no heredoc by default
    new_command->redirects = redirects;
    new_command->arguments = args;
    new_command->environment = environment;
    
    // Resolve the executable path if arguments are provided
    new_command->executable = NULL;
    if (args && args[0])
        new_command->executable = ft_get_path(args[0], *environment);
    
    return (new_command);
}

/**
 * @brief Creates and initializes a new execution tree node
 * 
 * @param command Command to be executed at this node
 * @param token Token associated with this node (usually an operator)
 * @return Pointer to new node structure, NULL if allocation fails
 */
t_sh_node *create_exec_node(t_sh_cmd *command, t_sh_token *token)
{
    t_sh_node *new_node;
    
    // Allocate memory for the new node structure
    new_node = malloc(sizeof(t_sh_node));
    if (!new_node)
        return (NULL);
    
    // Initialize node properties
    new_node->command = command;
    new_node->token = token;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return (new_node);
}

/**
 * @brief Creates and initializes a new token structure
 * 
 * @param content String content of the token
 * @param type Type classification of the token
 * @return Pointer to new token structure, NULL if allocation fails
 */
t_sh_token *create_token(char *content, t_token_kind type)
{
    t_sh_token *new_token;
    
    // Allocate memory for the new token structure
    new_token = malloc(sizeof(t_sh_token));
    if (!new_token)
        return (NULL);
    
    // Initialize token properties
    new_token->content = content;
    new_token->type = type;
    new_token->next = NULL;
    new_token->prev = NULL;
    
    return (new_token);
}

/**
 * @brief Creates and initializes a new process ID tracking structure
 * 
 * @param pid Process ID to track
 * @return Pointer to new PID structure, NULL if allocation fails
 */
t_sh_pid *create_process_tracker(pid_t pid)
{
    t_sh_pid *new_tracker;
    
    // Allocate memory for the new process tracker
    new_tracker = malloc(sizeof(t_sh_pid));
    if (!new_tracker)
        return (NULL);
    
    // Initialize tracker properties
    new_tracker->pid = pid;
    new_tracker->next = NULL;
    
    return (new_tracker);
}

/**
 * @brief Creates and initializes a new pipe information structure
 * 
 * @param read_fd File descriptor for reading from the pipe
 * @param write_fd File descriptor for writing to the pipe
 * @return Pointer to new pipe structure, NULL if allocation fails
 */
t_sh_pipe *create_pipe_info(int read_fd, int write_fd)
{
    t_sh_pipe *new_pipe;
    
    // Allocate memory for the new pipe info structure
    new_pipe = malloc(sizeof(t_sh_pipe));
    if (!new_pipe)
        return (NULL);
    
    // Initialize pipe properties
    new_pipe->fds[0] = read_fd;
    new_pipe->fds[1] = write_fd;
    new_pipe->next = NULL;
    
    return (new_pipe);
}

/**
 * @brief Creates and initializes a new execution context structure
 * 
 * @return Pointer to new execution context, NULL if allocation fails
 */
t_sh_exec *create_execution_context(void)
{
    t_sh_exec *new_context;
    
    // Allocate memory for the new execution context
    new_context = malloc(sizeof(t_sh_exec));
    if (!new_context)
        return (NULL);
    
    // Initialize context with empty pipe and process lists
    new_context->active_pipes = NULL;
    new_context->running_procs = NULL;
    
    return (new_context);
}
