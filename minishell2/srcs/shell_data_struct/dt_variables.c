#include "../../includes/minishell.h"

void    sh_add_env(t_sh_env **env, t_sh_env *new)
{
    t_sh_env    *tmp;

    if (!env || !new)
        return;
    if (!(*env))
    {
        *env = new;
        return;
    }
    tmp = *env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void    sh_remove_env(t_sh_env **env, char *key)
{
    t_sh_env    *prev;
    t_sh_env    *tmp;
    t_sh_env    *head;

    tmp = *env;
    prev = tmp;
    head = NULL;
    while (tmp && ft_strcmp(tmp->key, key))
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (prev == tmp)
        head = tmp->next;
    if (tmp && prev)
    {
        prev->next = tmp->next;
        sh_free_env(tmp);
    }
    if (head)
        *env = head;
}

void    sh_free_env(t_sh_env *env)
{
    free(env->key);
    if (env->values && *(env->values))
        ft_free_tab((void **) env->values);
    else
        free(env->values);
    free(env);
}

void    sh_clear_env(t_sh_env *env)
{
    t_sh_env    *tmp;

    while (env)
    {
        tmp = env->next;
        sh_free_env(env);
        env = tmp;
    }
}