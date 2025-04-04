#include "../../includes/minishell.h"

extern int  g_exit_code;

/**
 * @brief Returns the part of the path after the last '/'
 * 
 * What it does:
 * - Finds the last occurrence of '/' in the string and returns everything after it.
 * - If there is no '/' found, it returns an empty string.
 * 
 * @param str The input string representing a path.
 * @return A new string containing the last segment of the path or an empty string if no '/' is found.
 */
char    *sh_trim_pwd(char *str)
{
    char    *last_slash;

    // Find the last occurrence of '/' in the string
    last_slash = ft_strrchr(str, '/');
    if (!last_slash)
        return (ft_strdup("")); // Return an empty string if no '/' is found
    return (ft_strdup(last_slash)); // Return the substring starting from the last '/'
}


/**
 * @brief Retrieves the current working directory.
 * 
 * What it does:
 * - Uses `getcwd` to retrieve the current working directory and returns it as a string.
 * - If `getcwd` fails, it returns `NULL`.
 * 
 * @return A newly allocated string containing the current working directory, or `NULL` if it fails.
 */
char    *sh_get_cwd(void)
{
    char    cwd[65536];

    // Retrieve the current working directory
    if (getcwd(cwd, sizeof(cwd)))
        return (ft_strdup(cwd));  // Return the cwd as a newly allocated string
    return (NULL);  // Return NULL if getcwd fails
}

/**
 * @brief Executes the pwd built-in command.
 * 
 * What it does:
 * - Retrieves the current working directory and prints it to the specified output.
 * - If `getcwd` fails, it prints an error message and returns an error code.
 * 
 * @param cmd The command structure containing the output file descriptor.
 * @return `ERR_NONE` if successful, `ERR_FAIL` if there is an error.
 */
int     sh_execute_pwd(t_sh_cmd *cmd)
{
    char    cwd[65536];

    // Retrieve the current working directory
    if (getcwd(cwd, sizeof(cwd)))
        ft_dprintf(cmd->outfile, "%s\n", cwd);  // Print the cwd to the output
    else
    {
        perror("getcwd() error");
        return (ERR_FAIL);  // Return error if getcwd fails
    }
    return (ERR_NONE);  // Return success
}


/**
 * @brief Generates the prompt string for the shell.
 * 
 * What it does:
 * - Retrieves the current working directory (`PWD`) from the environment.
 * - Constructs a prompt string using the working directory and the shell's exit status.
 * 
 * @param envp The environment variables, used to get the `PWD` value.
 * @return A newly allocated string representing the shell prompt.
 */
char    *sh_get_prompt(t_sh_env *envp)
{
    static  t_sh_env *saved_env = NULL;
    char    *prompt;
    char    *pwd;

    if (envp)
        saved_env = envp;  // Save the environment variables if provided
    
    // Retrieve the current working directory (PWD) from the environment
    if (sh_find_env(saved_env, "PWD"))
    {
        pwd = trim_pwd(sh_find_env(saved_env, "PWD")->values[0]);
        pwd = ft_strjoin(pwd, " ~ ", 0, 0b01);  // Append " ~ " to the path
    }
    else
        pwd = ft_strdup(" ~ ");  // If PWD is not found, use " ~ "
    
    // Construct the prompt based on the exit code
    if (!g_exit_code)
        prompt = ft_strjoin(P_SUCCESS, P_TAIL, 0, 0b00);  // Success exit code
    else
        prompt = ft_strjoin(P_FAIL, P_TAIL, 0, 0b00);  // Failure exit code
    
    // Combine the prompt with the current working directory
    prompt = ft_strjoin(prompt, pwd, 0, 3);
    
    return (prompt);  // Return the final prompt string
}
