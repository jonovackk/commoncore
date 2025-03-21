#include "../../includes/minishell.h"

void      sh_append_token(t_sh_token **list, t_sh_token *new_tok)
{
    t_sh_token  *tmp;

    if (!list || !new_tok)
        return;
    if (!(*list))
    {
        *list = new_tok;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_tok;
    new_tok->prev = tmp;
}

void      sh_delete_token(t_sh_token **list)
{
    t_sh_token  *tmp;

    if ((*list)->prev)
    {
        tmp = *list;
        (*list)->prev->next = tmp->next;
        if (tmp->next)
            tmp->next->prev = (*list)->prev;
        *list = (*list)->prev->next;
        sh_token_free(tmp);
    }
    else
    {
        tmp = *list;
        *list = tmp->next;
        if (tmp->next)
            (*list)->prev = NULL;
        sh_token_free(tmp);
    }
}

t_sh_token  *sh_clone_token(t_sh_token *tok)
{
    t_sh_token  *cpy;

    cpy = malloc(sizeof(t_sh_token));
    if (!cpy)
        return (NULL);
    cpy->content = ft_strdup(tok->content);
    cpy->type = tok->type;
    cpy->next = NULL;
    cpy->prev = NULL;
    return (cpy);
}

void      sh_token_free(t_sh_token *tok)
{
    if (!tok)
        return;
    free(tok->content);
    free(tok);
}

void      sh_free_token_list(t_sh_token *list)
{
    t_sh_token  *tmp;

    while (list)
    {
        tmp = list->next;
        sh_token_free(list);
        list = tmp;
    }
}