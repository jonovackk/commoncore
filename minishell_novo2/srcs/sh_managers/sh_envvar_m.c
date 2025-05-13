/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_envvar_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:03 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:07:04 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    sh_append_env(t_sh_env **env, t_sh_env *new)
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

void    sh_delete_env(t_sh_env **env, char *key)
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
        sh_destroy_env_node(tmp);
    }
    if (head)
        *env = head;
}

void    sh_destroy_env_node(t_sh_env *env)
{
    free(env->key);
    if (env->values && *(env->values))
        ft_free_tab((void **) env->values);
    else
        free(env->values);
    free(env);
}

void    sh_destroy_env_list(t_sh_env *env)
{
    t_sh_env    *tmp;

    while (env)
    {
        tmp = env->next;
        sh_destroy_env_node(env);
        env = tmp;
    }
}