/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quote_procs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:32 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/13 10:30:20 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_shell_exit_status;

/**
 * @brief Ensures quotes are properly closed in the input line.
 * 
 * Core responsibilities:
 * 1. Traverse the input line and update quote state.
 * 2. If an unclosed quote is detected, retrieve additional input.
 * 3. Recursively enforce quote closure.
 * 4. Store the corrected line and reset quote tracking.
 * 
 * @param line Pointer to the input line (modified in place).
 * @param tmp_fd Temporary file descriptor for quote buffering.
 * @param state Current quote state.
 */
void sh_handle_unclosed_quotes(char **line, int tmp_fd, t_quote_state state)
{
    char *orig;
    char *dq_buf;

    if (!*line)
        return;

    orig = *line;
    sh_double_quote_state(*line, 0); // Initialize quote tracking

    // Traverse line and update quote state
    while (**line)
        sh_update_quote_state(*((*line)++), &state);

    // If an unclosed quote remains, retrieve additional input
    if (state)
    {
        dq_buf = sh_opendquote(tmp_fd, state);
        if (!dq_buf)
        {
            free(dq_buf);
            *line = orig;
            return;
        }

        // Append new input to original line and enforce quotes again
        dq_buf = ft_strjoin(orig, dq_buf, "\n", 0b11);
        sh_handle_unclosed_quotes(&dq_buf, tmp_fd, QUOTE_NONE);
        sh_double_quote_state(dq_buf, 0);
        *line = dq_buf;
        return;
    }
    
    *line = orig; // Restore original line pointer if no changes
}

/**
 * @brief Detects unclosed quotes and returns the quote state.
 * 
 * Core responsibilities:
 * 1. Traverse the input string while tracking quote state.
 * 2. Identify if a quote is left unclosed.
 * 3. If an end marker is provided, set it to the unclosed quote type.
 * 
 * @param line The input string to check.
 * @param end_marker Pointer to store the unclosed quote character (optional).
 * @param state Current quote state.
 * @return The final quote state after processing the string.
 */
t_quote_state sh_detect_quotes(char *line, char *end_marker, t_quote_state state)
{
    while (*line)
        sh_update_quote_state(*(line++), &state);

    // If an end marker is provided, store the type of unclosed quote
    if (end_marker && state == QUOTE_SINGLE)
        *end_marker = '\'';
    else if (end_marker && state == QUOTE_DOUBLE)
        *end_marker = '"';

    return state;
}

/**
 * @brief Removes quotes from a string while maintaining content integrity.
 * 
 * Core responsibilities:
 * 1. Allocate a new buffer to store the unquoted string.
 * 2. Traverse the original string, skipping quote characters.
 * 3. Copy non-quote characters into the new buffer.
 * 4. Free the original string and update the pointer.
 * 
 * @param line Pointer to the string to be modified.
 * @param state Current quote state.
 */
void sh_rmv_quotes(char **line, t_quote_state state)
{
    (void)state;
    
    printf("ANTES : [%s]\n", *line);
    char *src = *line;
    char *dst = malloc(strlen(*line) + 1);
    char *res_ptr = dst;
    int in_single = 0;
    int in_double = 0;

    if (!dst)
        return;

    while (*src)
    {
        if (*src == '\'' && !in_double)
        {
            in_single = !in_single;
            src++;
            continue;
        }
        else if (*src == '\"' && !in_single)
        {
            in_double = !in_double;
            src++;
            continue;
        }

        *res_ptr++ = *src++;
    }

    *res_ptr = '\0';
    free(*line);
    *line = dst;

    printf("DEPOIS: [%s]\n", *line);
}
