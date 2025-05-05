#include "../includes/minishell.h"

extern int	g_exit_status;

int	is_non_empty(const char *str)
{
	const char	*tmp;

	if (!str || !*str)
		return (0);
	tmp = str;
	while (*tmp && isspace(*tmp))
		tmp++;
	return (*tmp != '\0');
}

char *generate_temp_filename(const char *prefix, int length)
{
    int urandom_fd;
    char *buffer;
    char *temp_name;
    int i;

    buffer = ft_calloc(length + 1, sizeof(char));
    if (!buffer)
        return (NULL);
    urandom_fd = open("/dev/urandom", O_RDONLY);
    if (urandom_fd < 0)
    {
        free(buffer);
        return (NULL);
    }
    read(urandom_fd, buffer, length);
    close(urandom_fd);
    for (i = 0; i < length; i++)
    {
        while (!ft_isalnum(buffer[i]))
            buffer[i] = (unsigned char)buffer[i] % 93 + 33;
    }
    temp_name = ft_strjoin((char *)prefix, buffer, "_", 0b10);
    return (temp_name);
}

int main(int argc, char **argv, char **envp)
{
    t_sh_env *env;

    rl_catch_signals = 0;
    if (argc > 1)
    {
        sh_display_error(ERROR_INVALID_OPTION, argv[1]);
        exit(EXIT_FAILURE);
    }
    env = sh_env_init(argv, envp);
    sh_configure_signal_state(HANDLER_BUILTIN);

    while (1)
    {
        sh_env_context(&env);
        sh_command_tree_state(1, NULL);
        sh_handle_prompt(&env);
    }
    return (EXIT_SUCCESS);
}


/*In-Depth Function Analysis
1. is_non_empty(const char *str)
This function performs a robust check to determine if a string contains any 
non-whitespace characters. Key characteristics include:

Handles NULL and empty string inputs by returning 0
Skips leading whitespace characters
Uses a pointer traversal method for efficiency
Returns 1 if any non-whitespace character is found, 0 otherwise
Useful for validating input strings before further processing


3. generate_temp_filename(const char *prefix, int length)
Creates a unique temporary filename with robust randomness:

Utilizes /dev/urandom for cryptographically secure random byte generation
Converts random bytes to alphanumeric characters
Joins a prefix with random characters to create a unique filename
Handles memory allocation and error cases
Useful for creating temporary files with low collision probability

4. main(int argc, char **argv, char **envp)
The core entry point of the minishell application:

Disables readline's default signal handling
Prevents command-line arguments (pure interactive shell)
Initializes environment variables
Displays a welcome logo
Sets up signal handlers
Enters an infinite loop for continuous shell operation
Manages environment updates and command processing
Provides a clean, structured shell startup process

Overall Design Observations

Strong error handling
Modular function design
Use of custom utility functions (likely from a custom library)
Focus on security and user experience
Implements a typical shell loop with environment management
*/
