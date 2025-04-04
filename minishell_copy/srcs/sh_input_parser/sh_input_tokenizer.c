#include "../../includes/minishell.h"

/**
 * @brief Checks if the given input is a valid operator.
 * 
 * Core responsibilities:
 * 1. Validate if the input is empty or contains whitespace outside quotes.
 * 2. Compare input against a predefined list of shell operators.
 * 3. Return the length of the matching operator, or 1 if invalid.
 * 
 * @param input The string to check.
 * @param qstat The current quote state.
 * @return The length of the matching operator, or 1 if invalid.
 */
int sh_is_shell_operator(char *input, t_qstate qstat)
{
    char        **current;
    static char *operators[11] = {" ", "(", ")", "||", "&&", \
                                "|", ">>", ">", "<<", "<", NULL};

    current = operators;
    if (!input || !*input)
        return (1); // Return 1 if input is empty

    if (ft_isspace(*input) && qstat == QUOTE_NONE)
        return (1); // Ignore leading whitespace if not inside quotes

    // Iterate through the list of operators to find a match
    while (*current && (ft_strncmp(input, *current, ft_strlen(*current)) || qstat != QT_NONE))
        current++;

    return (ft_strlen(*current)); // Return operator length if found
}

/**
 * @brief Determines the token category of the input.
 * 
 * Core responsibilities:
 * 1. Return TOKEN_TEXT if inside quotes.
 * 2. Identify different shell token types (parentheses, logical, pipe, redirect).
 * 3. Default to TOKEN_TEXT if no category matches.
 * 
 * @param input The input string to categorize.
 * @param qstat The current quote state.
 * @return The corresponding token kind.
 */
t_token_kind sh_classify_token(char *input, t_qstate qstat)
{
    if (qstat != QUOTE_NONE)
        return (TOKEN_TEXT); // If inside quotes, treat as plain text

    // Check for parentheses
    if (!ft_strncmp(input, "(", 1) || !ft_strncmp(input, ")", 1))
        return (TOKEN_PARENTHESIS);

    // Check for logical operators (&&, ||)
    if (!ft_strncmp(input, "||", 2) || !ft_strncmp(input, "&&", 2))
        return (TOKEN_LOGICAL);

    // Check for pipe symbol '|'
    if (!ft_strncmp(input, "|", 1))
        return (TOKEN_PIPE);

    // Check for redirection operators ('<' or '>')
    if (!ft_strncmp(input, ">", 1) || !ft_strncmp(input, "<", 1))
        return (TOKEN_REDIRECT);

    return (TOKEN_TEXT); // Default to plain text token
}

/**
 * @brief Parses input into a linked list of tokens.
 * 
 * Core responsibilities:
 * 1. Identify and extract valid tokens from input.
 * 2. Handle spaces and quotes while tokenizing.
 * 3. Recursively process remaining input into tokens.
 * 4. Append new tokens to the result list.
 * 
 * @param input The input string to parse.
 * @param qstat The current quote state.
 * @return A linked list of tokens.
 */
t_sh_token *sh_tokenize_input(char *input, t_qstate qstat)
{
    t_sh_token *result;
    char    *token_content;
    char    *current_pos;
    int     token_length;

    result = NULL;
    if (!input || !*input)
        return (NULL); // Return NULL if input is empty

    current_pos = input;
    token_length = sh_is_shell_operator(current_pos, qstat);

    // Skip spaces and update quote state while processing input
    while (*current_pos && (!token_length || (ft_isspace(*current_pos) && qstat != QT_NONE)))
    {
        sh_update_quote_state(*(current_pos++), &qstat);
        token_length = sh_is_shell_operator(current_pos, qstat);
    }

    // Extract token based on position in the input string
    if (current_pos == input)
        token_content = ft_strndup(input, token_length);
    else
        token_content = ft_strndup(input, current_pos - input);

    if (ft_strncmp(token_content, " ", 2)) // Ignore standalone spaces as tokens
        result = sh_create_token(ft_strdup(token_content), sh_classify_token(input, qstat));

    // Recursively parse the rest of the input
    append_token(&result, parse_into_tokens(input + ft_strlen(token_content), qstat));

    free(token_content);
    return (result);
}

/**
 * @brief Checks if the input contains an unquoted wildcard (*).
 * 
 * Core responsibilities:
 * 1. Iterate through the input to check for '*' characters.
 * 2. Maintain quote state to differentiate quoted vs. unquoted wildcards.
 * 3. Return 1 if an unquoted wildcard is found, 0 otherwise.
 * 
 * @param input The input string to check.
 * @param qstat The current quote state.
 * @return 1 if an unquoted wildcard exists, 0 otherwise.
 */
int sh_contains_unquoted_wildcard(char *input, t_qstate qstat)
{
    char *current_pos;

    current_pos = input;
    while (*current_pos)
    {
        sh_update_quote_state(*current_pos, &qstat);

        // If '*' is found and not inside quotes, return true
        if (*current_pos == '*' && qstat == QUOTE_NONE)
            return (1);

        current_pos++;
    }
    return (0);
}

/**
 * @brief Expands '~' in tokens to the home directory value.
 * 
 * Core responsibilities:
 * 1. Traverse the token list to find '~' tokens.
 * 2. Replace '~' with the value of the home directory variable.
 * 3. Preserve the linked list structure.
 * 
 * @param token_list Pointer to the token list.
 * @param home_var The home environment variable.
 */
void sh_expand_tilde(t_sh_token **token_list, t_envvar *home_var)
{
    t_sh_token *current;

    current = *token_list;
    while (current)
    {
        // Check if token is '~' and replace it with the home directory path
        if (!ft_strncmp(current->str, "~", 2))
        {
            if (home_var)
            {
                free(current->str);
                current->str = sh_format_env_var(home_var, 0, 0);
            }
            current = current->next;
        }
        else
            current = current->next;
    }
}
