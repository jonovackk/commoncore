#include "../../includes/minishell.h"

extern int g_exit_code;

/**
 * @brief Calculates the length of an environment variable.
 * 
 * This function calculates the length of a variable name, considering whether it starts with a special character
 * such as `$` or `?`, and whether it's followed by valid alphanumeric characters or underscores.
 * 
 * @param str The string representing the environment variable.
 * @return The length of the environment variable.
 */
int sh_get_env_var_length(char *str)
{
    char *ptr = str + 1;  // Skip the initial '$' or other special character.
    
    // If no characters after the initial, it's just the special character (e.g., $?).
    if (!*ptr)
        return 1;
    
    // Handle cases where the variable starts with a number or a quote.
    if (ft_isdigit(*ptr) || ft_strchr("\"'", *ptr))
        return 2;
    
    // If the first character is not valid (not alphanumeric or "_?"), return length 1.
    if (!ft_strchr("_?", *ptr) && !ft_isalnum(*ptr))
        return 1;
    
    // If the character is "?", return length 2 (e.g., $?).
    if (*ptr == '?')
        return 2;

    // Move the pointer ahead while valid characters are encountered.
    ptr++;
    while (*ptr && (ft_isalnum(*ptr) && !ft_strchr("_?", *ptr)))
        ptr++;

    // Return the length of the variable name.
    return (ptr - str);
}

/**
 * @brief Skips over any quoted sections in the string.
 * 
 * This function helps to handle quoted sections (single or double quotes) by updating
 * the quote state and decrementing the remaining length to be processed.
 * 
 * @param s The string to process.
 * @param rem The remaining length to process.
 * @param state The state of the quotes being processed.
 */
void sh_process_quoted_section(char **s, int *rem, t_quote_state *state)
{
    while (*s && **s && ((*rem) > 0))
    {
        sh_update_quote_state(*((*s)++), state);  // Update the quote state for the current character.
        (*rem)--;  // Decrement the remaining length.
    }
}

/**
 * @brief Inserts the value of an environment variable into the result parts.
 * 
 * This function checks for special cases such as the "exit code" ($?) and handles the insertion of environment variables.
 * It finds the environment variable and inserts its value into the result parts.
 * 
 * @param env The environment variables structure.
 * @param s The string containing the variable to insert.
 * @param res_parts The parts of the result string that will be populated.
 * @param state The current state of quotes in the string.
 */
void sh_insert_env_vars(t_sh_env *env, char *s, char ***res_parts, t_quote_state state)
{
    t_sh_env *env_var;
    char *key;
    int key_len;

    (void) state;  // 'state' is not used here, but it's kept for consistency.

    // Handle special case for exit code ('$?')
    if (*s && *(s + 1) == '?')
    {
        ft_strapp(res_parts, ft_itoa(g_exit_code));  // Append exit code to result parts.
        return;
    }

    s++;  // Skip the '$' character.
    
    // If the next character is a digit, return without inserting anything.
    if (ft_isdigit(*s))
        return;

    // Calculate the length of the environment variable's key.
    key_len = sh_get_env_var_length(s - 1);

    // Handle the case where the key starts with a quote.
    if (ft_strchr("\"'", *s))
        ft_strapp(res_parts, ft_strndups(s - 1, 2));

    // If it's a quoted string, stop processing.
    if (ft_strchr("\"'", *s))
        return;

    // Extract the key (variable name) and find its value in the environment.
    key = ft_strndup(s, key_len - 1);
    env_var = sh_find_env(env, key);

    // If the variable is not found, insert an empty string, otherwise insert its value.
    if (!env_var)
        ft_strapp(res_parts, ft_strdup(""));
    else
        ft_strapp(res_parts, sh_format_env_var(env_var, 0, 0));

    // Free the allocated memory for the key.
    free(key);
}

/**
 * @brief Replaces environment variables in a string with their values.
 * 
 * This function processes the input string and replaces any environment variable placeholders
 * (e.g., $HOME, $? etc.) with their corresponding values from the environment.
 * 
 * @param env The environment variables structure.
 * @param line The string to process, which may contain environment variable placeholders.
 * @param state The current state of quotes in the string.
 */
void sh_replace_env_vars(t_sh_env *env, char **line, t_quote_state state)
{
    int seg_len;
    char *ptr;
    char **parts;

    ptr = *line;  // Pointer to the current position in the line.
    parts = NULL;  // Parts will hold the result.

    // If no line is provided, return early.
    if (!ptr)
        return;

    // Process each segment of the line.
    while (*ptr)
    {
        // Get the length of the segment until the next '$' symbol.
        seg_len = ft_strcspn(ptr, "$");
        ft_strapp(&parts, ft_strndup(ptr, seg_len));  // Append the segment to parts.

        // Skip any quoted sections.
        sh_process_quoted_section(&ptr, &seg_len, &state);

        // If no more characters are left, break.
        if (!*ptr)
            break;

        // If the state is not a single quote and the variable length is greater than 1, process the environment variable.
        if (state != QUOTE_SINGLE && sh_get_env_var_length(ptr) > 1)
        sh_insert_env_vars(env, ptr, &parts, state);
        else
            ft_strapp(&parts, ft_strndup(ptr, sh_get_env_var_length(ptr)));  // Append non-variable part.

        // Move the pointer forward by the length of the processed variable.
        ptr += sh_get_env_var_length(ptr);
    }

    // Free the old line and join the parts into the new line.
    free(*line);
    *line = ft_strsjoin(parts, NULL, 0b01);
}


// possible errors on this file pay attention