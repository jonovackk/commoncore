#include "../../includes/minishell.h"

/**
 * @brief Updates the quote status based on the given character.
 * 
 * Core responsibilities:
 * 1. If currently outside quotes, detect opening quote type.
 * 2. If inside matching quotes, detect closing quote.
 * 3. Return whether the quote status changed.
 * 
 * @param c The character to evaluate.
 * @param qstatus Pointer to the current quote state.
 * @return 1 if the quote state changed, 0 otherwise.
 */
int sh_update_quote_state(char c, t_qstate *qstatus)
{
    t_qstate previous;

    previous = *qstatus; // Store the previous state

    if (*qstatus == QUOTE_NONE)
    {
        if (c == '\'')
            *qstatus = QUOTE_SINGLE; // Enter single-quote mode
        if (c == '"')
            *qstatus = QUOTE_DOUBLE; // Enter double-quote mode
    }
    else if ((c == '\'' && *qstatus == QUOTE_SINGLE) || (c == '"' && *qstatus == QT_DOUBLE))
        *qstatus = QUOTE_NONE; // Exit quotes if closing match is found

    return (*qstatus != previous); // Return whether the state changed
}

/**
 * @brief Counts characters in a string, ignoring quoted sections.
 * 
 * Core responsibilities:
 * 1. Iterate through the string while tracking quote state.
 * 2. Only count characters that are not part of a quoted segment.
 * 3. Return the number of non-quoted characters.
 * 
 * @param str The input string.
 * @return The number of characters outside quotes.
 */
int sh_ignoring_quotes(char *str)
{
    t_qstate qstatus;
    int length;

    qstatus = QUOTE_NONE; // Start with no active quotes
    length = 0;

    while (*str)
    {
        // Update quote state; if unchanged, count the character
        if (!sh_update_quote_state(*(str++), &qstatus))
            length++;
    }
    return (length);
}

/**
 * @brief Cleans up invalid parenthesis tokens from the token list.
 * 
 * Core responsibilities:
 * 1. Iterate through the token list.
 * 2. Check if parentheses are logically valid.
 * 3. Remove invalid parenthesis tokens and adjust list structure.
 * 
 * @param tokens Pointer to the list of tokens.
 */
void sh_rmv_inv_parentheses(t_sh_token **tokens)
{
    t_sh_token *current;

    current = *tokens;
    while (current)
    {
        // If the current token has invalid parentheses, remove it
        if (!sh_check_ops_in_brackets(current))
        {
            delet_token(&current); // Delete invalid token

            if (!current)
            {
                *tokens = NULL; // If list is empty, reset it
                continue;
            }

            // Update head of list if first token was removed
            if (!current->prev)
                *tokens = current;

            continue;
        }
        current = current->next;
    }
}
