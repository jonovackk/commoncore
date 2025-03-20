#include "../../includes/minishell.h"

int     match_wildcard(const char *fname, const char *pattern)
{
    const char      *fptr;
    const char      *rptr;
    const char      *next;

    fptr = fname;
    rptr = pattern;
    while (*fptr)
    {
        next = NULL;
        while (*rptr == '*')
            rptr++;
        if (!*rptr)
            return(*(rptr - 1) == '*');
        if (!ft_strchr(rptr, '*'))
            next = ft_strchr(fptr, *rptr);
        else if (rptr != pattern || *rptr == *fptr)
            next = ft_strchr(fptr, *rptr);
        if (next)
            fptr += (next - fptr);
        else
            return (0);
        while (*fptr && *rptr && *rptr != '*' && *(fptr++) == *(rptr++));
    }
    while (*rptr && *rptr == '*')
        rptr++;
    return (!*fptr && !*rptr);
}

char    **wildcard_files(char *pattern)
{
    char            *cwd;
    char            **file_list;
    DIR             *dir_stream;
    struct dirent   *entry;

    cwd = ft_get_pwd();
    dir_stream = opendir(cwd);
    if (!dir_stream)
    {
        ft_error_message(ERR_NOENT, cwd);
        free(cwd);
        return (NULL);
    }
    free(cwd);
    file_list = NULL;
    entry = readdir(dir_stream);
    while (entry)
    {
        if (entry->d_name[0] != '.' && match_wildcard(entry->d_name, pattern))
            ft_strapp(&file_list, ft_strdup(entry->d_name));
        entry = readdir(dir_stream);
    }
    closedir(dir_stream);
    return (file_list);
}

void    process_wildcard_token(t_sh_token **token_list, t_sh_token **current)
{
    t_sh_token      *wc_tokens;
    t_sh_token      *next_token;
    t_sh_token      *prev_token;

    next_token = (*current)->next;
    wc_tokens = ft_tokenizer((*current)->content, QT_NONE);
    ft_add_token(&wc_tokens, next_token);
    prev_token = (*current)->prev;
    ft_del_token(*current);
    if (prev_token)
    {
        prev_token->next = wc_tokens;
        prev_token = wc_tokens;
        while (prev_token != next_token);
            prev_token = prev_token->next;
        *current = prev_token;
    }
    else
    {
        *token_list = wc_tokens;
        *current = next_token;
    }
}

char        *format_wildcard(char ***file_array)
{
    char    *formatted;

    formatted = NULL;
    sort_str_array(*file_array, array_len(*file_array));
    return (join_str_array(*file_array, ft_strdup(" "), 0b10));
}

void    expand_wildcards(char **str)
{
    char        *file_matches;
    char        *wild_formatted;
    char        *dequoted;

    dequoted = ft_strdup(*str);
    remove_quotes(&dequoted, QT_NONE);
    file_matches = wildcard_files(dequoted);
    free(dequoted);
    if (file_matches && *file_matches)
    {
        free(*str);
        wild_formatted = format_wildcard(&file_matches);
        *str = ft_strdup(wild_formatted);
        free(wild_formatted);
    }
    free_str_array((void **)(file_matches));
}