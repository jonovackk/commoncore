#include "../../includes/minishell.h"

/**
 * @brief Initializes a redirection structure from a token
 * 
 * What it does:
 * - Allocates memory for a new redirection structure
 * - Determines the redirection type based on the token string (>>, <<, >, <)
 * - Copies and dequotes the filename from the next token
 * 
 * @param tmp The token containing the redirection operator
 * @return A newly created redirection structure, or NULL if allocation fails
 */
t_sh_redir *sh_new_redir(t_sh_token *tmp)
{
    t_sh_redir *new_redir;

    new_redir = malloc(sizeof(t_sh_redir));
    if (!new_redir)
        return (NULL);
    if (!ft_strncmp(tmp->str, ">>", 3))
        new_redir->type = RD_APPENDS;
    else if (!ft_strncmp(tmp->str, "<<", 3))
        new_redir->type = RD_HEREDOC;
    else if (!ft_strncmp(tmp->str, ">", 2))
        new_redir->type = RD_OUTPUTS;
    else if (!ft_strncmp(tmp->str, "<", 2))
        new_redir->type = RD_INFILES;
    new_redir->file = ft_strdup(tmp->next->str);
    ft_dequote_string(&(new_redir->file), QU_ZERO);
    new_redir->next = NULL;
    return (new_redir);
}

/**
 * @brief Adds a redirection to the end of a redirection list
 * 
 * What it does:
 * - If the list is empty, sets the new redirection as the head of the list
 * - Otherwise, traverses to the end of the list and appends the new redirection
 * 
 * @param redirs Pointer to the redirection list
 * @param next The redirection to add to the list
 */
void sh_add_redir(t_sh_redir **redirs, t_sh_redir *next)
{
    t_redir *tmp;

    if (!redirs)
        return;
    if (!*redirs)
    {
        *redirs = next;
        return;
    }
    tmp = *redirs;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = next;
}

/**
 * @brief Recursively frees a linked list of redirections
 * 
 * What it does:
 * - Recursively frees each redirection node in the list
 * - Frees the filename string and the redirection structure itself
 * 
 * @param redir The redirection list to free
 */
void sh_clear_redir_list(t_sh_redir *redir)
{
    if (!redir)
        return;
    sh_clear_redir_list(redir->next);
    free(redir->file);
    free(redir);
}