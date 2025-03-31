#include "../../includes/minishell.h"

/**
 * @brief Matches a filename against a wildcard pattern.
 * 
 * Core responsibilities:
 * 1. Skip consecutive '*' characters in the pattern.
 * 2. Check for character matches between the filename and pattern.
 * 3. Return 1 if the filename matches the pattern, otherwise return 0.
 * 
 * @param filename The filename to check.
 * @param pattern The wildcard pattern.
 * @return 1 if there's a match, 0 otherwise.
 */
int sh_match_wildcard(const char *filename, const char *pattern)
{
    const char *file_ptr;
    const char *pat_ptr;
    const char *next_match;

    file_ptr = filename;
    pat_ptr = pattern;

    while (*file_ptr)
    {
        next_match = NULL;

        // Skip all consecutive '*' in the pattern
        while (*pat_ptr == '*')
            pat_ptr++;

        // If the pattern is fully consumed, return true if it ended with '*'
        if (!*pat_ptr)
            return (*(pat_ptr - 1) == '*');

        // Locate the next occurrence of the current pattern character in the filename
        if (!ft_strchr(pat_ptr, '*'))
            next_match = ft_strchr(file_ptr, *pat_ptr);
        else if (pat_ptr != pattern || *pat_ptr == *file_ptr)
            next_match = ft_strchr(file_ptr, *pat_ptr);

        // If no match is found, the pattern does not match the filename
        if (!next_match)
            return (0);

        // Move file pointer to the next match position
        file_ptr += (next_match - file_ptr);

        // Compare characters until encountering '*' or end of pattern
        while (*file_ptr && *pat_ptr && *pat_ptr != '*' && *(file_ptr++) == *(pat_ptr++));
    }

    // Skip any trailing '*' in the pattern
    while (*pat_ptr == '*')
        pat_ptr++;

    // Match is valid if both the filename and pattern are fully consumed
    return (!*file_ptr && !*pat_ptr);
}

/**
 * @brief Retrieves filenames matching a wildcard pattern in the current directory.
 * 
 * Core responsibilities:
 * 1. Open the current directory for reading.
 * 2. Filter filenames that match the given pattern.
 * 3. Return a dynamically allocated array of matches.
 * 
 * @param pattern The wildcard pattern.
 * @return Array of matching filenames, or NULL if no matches found.
 */
char **sh_get_matching_files(char *pattern)
{
    char *cwd;
    char **file_list;
    DIR *dir_stream;
    struct dirent *entry;

    cwd = sh_get_cwd();  // Get current working directory
    if (!cwd)
        return (NULL); // Possible error: `ft_get_pwd()` might return NULL

    dir_stream = opendir(cwd);  // Open directory stream
    if (!dir_stream)
    {
        sh_display_error(ERR_NO_ENTRY, cwd); // Print error if directory cannot be opened
        free(cwd);
        return (NULL);
    }
    free(cwd);

    file_list = NULL;
    entry = readdir(dir_stream);  // Read directory entries
    while (entry)
    {
        // Ignore hidden files (starting with '.') and match against the wildcard pattern
        if (entry->d_name[0] != '.' && sh_match_wildcard(entry->d_name, pattern))
            ft_strapp(&file_list, ft_strdup(entry->d_name));

        entry = readdir(dir_stream);
    }
    
    closedir(dir_stream);  // Close directory stream
    return (file_list);
}

/**
 * @brief Expands a wildcard token by replacing it with matching filenames.
 * 
 * Core responsibilities:
 * 1. Tokenize the wildcard pattern.
 * 2. Replace the original token with the expanded tokens.
 * 3. Maintain correct token list structure.
 * 
 * @param token_list The head of the token list.
 * @param current The current token being processed.
 */
void sh_expd_wildcard_token(t_sh_token **token_list, t_sh_token **current)
{
    t_sh_token *wc_tokens;
    t_sh_token *next_token;
    t_sh_token *prev_token;

    next_token = (*current)->next;  // Store reference to next token
    wc_tokens = sh_tokenize_input((*current)->content, QUOTE_NONE); // Tokenize wildcard content
    ft_add_token(&wc_tokens, next_token); // Append new tokens to the list

    prev_token = (*current)->prev; // Store reference to previous token
    ft_del_token(*current); // Remove original wildcard token

    if (prev_token)
    {
        prev_token->next = wc_tokens; // Link previous token to expanded tokens
        prev_token = wc_tokens;

        while (prev_token != next_token) // Traverse tokens until reaching original next token
            prev_token = prev_token->next;

        *current = prev_token; // Update current token position
    }
    else
    {
        *token_list = wc_tokens; // If no previous token, update head of the list
        *current = next_token;
    }
}

/**
 * @brief Formats a list of filenames into a space-separated string.
 * 
 * Core responsibilities:
 * 1. Sort the filenames for predictable output.
 * 2. Join them into a single string with spaces.
 * 3. Return the formatted result.
 * 
 * @param file_array Pointer to an array of filenames.
 * @return Space-separated string of filenames.
 */
char *sh_format_wildcard_matches(char ***file_array)
{
    char *formatted;

    formatted = NULL;
    sort_str_array(*file_array, array_len(*file_array)); // Sort filenames alphabetically
    return (join_str_array(*file_array, ft_strdup(" "), 0b10)); 
}

/**
 * @brief Expands wildcard patterns in a given string.
 * 
 * Core responsibilities:
 * 1. Remove quotes from the input.
 * 2. Retrieve matching filenames.
 * 3. Replace the original string with the expanded matches.
 * 
 * @param str Pointer to the string to expand.
 */
void sh_replace_wildcards(char **str)
{
    char *matched_files;
    char *formatted_output;
    char *unquoted_str;

    unquoted_str = ft_strdup(*str); // Duplicate original string
    if (!unquoted_str)
        return;

    sh_rmv_quotes(&unquoted_str, QUOTE_NONE); // Remove any surrounding quotes
    matched_files = sh_get_matching_files(unquoted_str); // Get files matching the pattern
    free(unquoted_str);

    if (matched_files && *matched_files) // Ensure there are matches before modifying input
    {
        free(*str);
        formatted_output = sh_format_wildcard_matches(&matched_files); // Format matches into a single string
        *str = ft_strdup(formatted_output);
        free(formatted_output);
    }

    free_str_array((void **)matched_files); // Free allocated file list
}
