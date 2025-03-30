#include "../../includes/minishell.h"

/**
 * @brief Calculates the size of the environment variable list.
 * 
 * What it does:
 * - Iterates through the linked list of environment variables and counts how many nodes it contains.
 * 
 * @param env The linked list of environment variables.
 * @return The number of environment variables in the list.
 */
int sh_env_list_size(t_sh_env *env)
{
    int size = 0;

    // Traverse the linked list and count the nodes
    while (env)
    {
        size++;
        env = env->next;
    }

    // Return the count of environment variables
    return (size);
}


/**
 * @brief Creates a formatted string representing an environment variable.
 * 
 * What it does:
 * - Constructs a string from the environment variable's key and values.
 * - Optionally includes the variable name (`key`) and applies a formatting style (e.g., adding quotes around the value).
 * 
 * @param env The environment variable structure containing the key and values.
 * @param format If non-zero, applies quotes around the values.
 * @param include_name If non-zero, includes the variable name (`key`) in the returned string.
 * @return A newly allocated string representing the environment variable in the desired format, or NULL if an error occurs.
 */
char *sh_format_env_var(t_sh_env *env, int format, int include_name)
{
    char *str = NULL;

    // If the environment variable is NULL, return NULL
    if (env == NULL)
        return (NULL);

    // If no values are present and the variable name should be included, return just the name
    if (!env->values && include_name)
        return (ft_strdup(env->key));

    // Include the variable name in the string if requested
    if (include_name)
        str = str_join(ft_strdu(env->key), "=", NULL, 0b01);

    // Apply the format if needed (e.g., add quotes around the values)
    if (format)
        str = str_join(str, "\"", NULL, 1);

    // Join the values (separated by colons) into the string
    str = str_join(str, join_str_array(env->values, ":", 0b00), NULL, 0b11);

    // Close the quotes if formatting is applied
    if (format)
        str = str_join(str, "\"", NULL, 0b01);

    return (str);
}


/**
 * @brief Converts a linked list of environment variables into an array of strings.
 * 
 * What it does:
 * - Iterates through the environment variable list and converts each variable to a formatted string.
 * - Each environment variable is added to an array, with its key and value(s) formatted according to the `format` argument.
 * 
 * @param env The linked list of environment variables.
 * @param format If non-zero, applies formatting to the environment variable strings (e.g., adding quotes).
 * @return A dynamically allocated array of strings representing the environment variables, or NULL if an error occurs.
 */
char **sh_create_env_array(t_sh_env *env, int format)
{
    int     i;
    int     size;
    char    **env_array;

    // Calculate the size of the environment list
    i = -1;
    size = var_list_size(env) + 1;

    // Allocate memory for the array of strings
    env_array = malloc(size * sizeof(char *));
    if (!env_array)
        return (NULL);

    // Iterate over the linked list of environment variables and convert each to a string
    while (++i < size - 1)
    {
        // Get the formatted string for each environment variable
        env_array[i] = get_env_string(env, format, 1);
        if (!env_array[i])
        {
            // If an error occurs, free the allocated memory and return NULL
            free_str_array((void **)env_array);
            return (NULL);
        }
        env = env->next;  // Move to the next environment variable in the list
    }

    // Terminate the array with a NULL pointer
    env_array[i] = NULL;

    return (env_array);  // Return the populated array of environment variable strings
}


/**
 * @brief Executes the `env` built-in command, printing the environment variables.
 * 
 * What it does:
 * - Checks if more than one argument is provided, returning an error if so.
 * - Retrieves the environment variables and prints each one in the format of key-value pairs.
 * - Each environment variable is printed only if it contains an '=' (key-value pair).
 * 
 * @param cmd The command structure containing the environment variables and output file descriptor.
 * @return ERR_NONE on success, or an error code on failure.
 */
int sh_execute_env(t_sh_cmd *cmd)
{
    t_sh_env    *env;
    char        **env_array;
    char        **tmp;

    // If there are more than one argument, print an error message and return an error code
    if (array_len(cmd->arguments) > 1)
    {
        print_error_message(ERR_ARGS, "env");
        return (127);  // Return error code for invalid arguments
    }

    // Get the environment list from the command structure
    env = *(cmd->environment);

    // Retrieve the environment variables as an array of strings
    env_array = get_env_string(env, 0);
    if (!env_array)
        return (ERR_FAIL);  // Return error if the environment array couldn't be retrieved

    // Iterate through the environment array and print each variable that includes '=' (key-value pair)
    tmp = env_array;
    while (*tmp)
    {
        if (ft_strchr(*tmp, '='))
            ft_dprintf(cmd->outfile, "%s\n", *tmp);  // Print environment variable
        tmp++;
    }

    // Free the memory allocated for the environment array
    free_str_array((void **)env_array);

    return (ERR_NONE);  // Return success
}
