#include "../../includes/minishell.h"

/**
 * @brief Checks the validity of a subtoken in a sequence.
 * 
 * This function verifies if a given token is logically placed within a sequence.
 * It ensures operators are followed by valid tokens and parentheses are correctly used.
 * 
 * @param token The current token in the sequence.
 * @return 1 if the token placement is valid, 0 otherwise.
 */
int sh_validate_subtoken(t_sh_token *token)
{
    t_token_kind binop_mask;
    t_token_kind str_mask;

    binop_mask = TOKEN_LOGICAL | TOKEN_PIPE;
    str_mask = TOKEN_TEXT | TOKEN_REDIRECT;

    // Prevent consecutive logical operators
    if ((token->type & TOKEN_LOGICAL) && (token->next->type & binop_mask))
        return (0);
    
    // Ensure redirections are followed by a valid token
    else if (token->type == TOKEN_REDIRECT && !(token->next->type & logical_mask))
        return (0);
    
    // Prevent pipes from being followed by logical operators
    else if (token->type == TOKEN_PIPE && (token->next->type & logical_mask))
        return (0);
    
    // Ensure valid parenthesis usage
    else if (!ft_strncmp(token->str, "(", 2) &&
             ((token->next->type & logical_mask) || !ft_strncmp(token->next->str, ")", 2)))
        return (0);

    // Prevent text tokens from being immediately followed by an opening parenthesis
    else if (token->type == TOKEN_TEXT && (token->next->type & TOKEN_PARENTHESIS) &&
             !ft_strncmp(token->next->str, "(", 2))
        return (0);

    // Prevent closing parenthesis being followed by text or another opening parenthesis
    else if (!ft_strncmp(token->str, ")", 2) &&
             (token->next->type & text_mask || !ft_strncmp(token->next->str, "(", 2)))
        return (0);
    
    return (1);
}

/**
 * @brief Validates the overall sequence of tokens.
 * 
 * Ensures that the token sequence follows proper syntax rules.
 * This includes checking for misplaced operators and verifying 
 * that the final token is valid.
 * 
 * @param token The starting token of the sequence.
 * @param err_token Pointer to store the problematic token if an error is found.
 * @return 1 if the sequence is valid, 0 otherwise.
 */
int sh_validate_syntax(t_sh_token *token, char **err_token)
{
    // Ensure the first token is not an operator
    if (token->type & (TOKEN_LOGICAL | TOKEN_PIPE))
        return (0);

    while (token->next)
    {
        *err_token = token->next->str;
        if (!check_subtoken_validity(token))
            return (0);
        token = token->next;
    }

    // Ensure the final token is either a valid command or a parenthesis
    return (token->type & (TOKEN_PARENTHESIS | TOKEN_TEXT));
}

/**
 * @brief Checks if parentheses are balanced in the token sequence.
 * 
 * Counts the number of opening and closing parentheses and ensures they are balanced.
 * 
 * @param tokens The list of tokens to check.
 * @return 1 if the parentheses are balanced, 0 otherwise.
 */
int sh_check_parenthesis_balance(t_sh_token *tokens)
{
    int balance = 0;

    while (tokens != NULL)
    {
        if ((tokens->type & TOKEN_PARENTHESIS) && !ft_strncmp(tokens->str, "(", 2))
            balance++;
        else if ((tokens->type & TOKEN_PARENTHESIS) && !ft_strncmp(tokens->str, ")", 2))
            balance--;

        // If a closing parenthesis appears before an opening one, it's invalid
        if (balance < 0)
            return (0);

        tokens = tokens->next;
    }

    return (balance == 0);
}

/**
 * @brief Verifies the validity of a token sequence.
 * 
 * This function performs multiple validation checks:
 * - Ensures correct operator usage.
 * - Ensures parentheses are balanced.
 * - Checks that the number of here-documents does not exceed the limit.
 * 
 * @param tokens The token sequence to verify.
 * @param err_token Pointer to store the problematic token if an error is found.
 * @return Error code: ERR_NONE if valid, ERR_FAILED if invalid, 0b100 if too many here-documents.
 */
int sh_validate_tokens(t_sh_token *tokens, char **err_token)
{
    t_sh_token *current;
    int here_doc_count;

    *err_token = tokens->str;

    // Ensure correct token sequence and balanced brackets
    if (!validate_token_sequence(tokens, err_token) || !check_bracket_balance(tokens))
        return (ERR_FAILED);

    current = tokens;
    here_doc_count = 0;

    // Count the number of here-document operators (<<)
    while (current)
    {
        here_doc_count += ((current->type & TOKEN_REDIRECT) && !ft_strncmp(current->str, "<<", 3));
        current = current->next;
    }

    // If the limit of 16 here-documents is exceeded, return an error
    if (here_doc_count > 16)
        return (0b100);

    return (ERR_NONE);
}

/**
 * @brief Validates that logical operators are correctly used within brackets.
 * 
 * Ensures that brackets do not enclose invalid sequences, such as a lack of operators.
 * If a sequence inside brackets is invalid, it removes the incorrect token.
 * 
 * @param token The starting token to check.
 * @return 1 if valid, 0 otherwise.
 */
int sh_check_ops_in_brackets(t_sh_token *token)
{
    int valid;
    int bracket_level;

    bracket_level = 0;
    valid = 0;

    // If the token isn't an opening parenthesis, return valid by default
    if (!token || !(token->type & TOKEN_PARENTHESIS && !ft_strncmp(token->str, "(", 2)))
        return (1);

    token = token->next;

    // Traverse tokens until the corresponding closing bracket is found
    while (token && (!(token->type & TOKEN_PARENTHESIS && !ft_strncmp(token->str, ")", 2)) || bracket_level))
    {
        if (token->type & TOKEN_PARENTHESIS && !ft_strncmp(token->str, "(", 2))
            bracket_level++;

        if (token->type & TOKEN_PARENTHESIS && !ft_strncmp(token->str, ")", 2))
            bracket_level--;

        // If a logical operator is found before closing, mark it as valid
        if (!bracket_level && (token->type & TOKEN_LOGICAL))
            valid = 1;

        token = token->next;
    }

    // If no closing bracket is found, return valid by default
    if (!token)
        return (1);

    // If the bracketed sequence is invalid, remove it
    if (!(token && valid))
        ft_remove_token(&token);

    return (token && valid);
}
