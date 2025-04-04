#include "../../includes/minishell.h"

t_sh_env    *sh_find_env(t_sh_env *env, char *key)
{
    while (env && ft_strncmp(env->key, key, ft_strlen(env->key) + 1))
        env = env->next;
    return (env);
}

t_sh_env    *sh_get_last_env(t_sh_env *env)
{
    while (env->next)
        env = env->next;
    return (env);
}

void    sh_update_env(t_sh_env **env, char *key, char *val)
{
    t_sh_env    *head;

    head = *(env);
    while (*(env) && ft_strncmp((*env)->key, key, ft_strlen(key)))
        *(env) = (*env)->next;
    if (!*(env))
    {
        sh_append_env(&head, sh_create_env_var(key));
        *(env) = sh_get_last_env(head);
    }
    ft_free_tab((void **)(*env)->values);
    (*env)->values = NULL;
    (*env)->values = ft_split(val, ':');
    *(env) = head;
    if (ft_strlen(val))
        free(val);
}

void    sh_extend_env(t_sh_env **env, char *key, char *val)
{
    t_sh_env    *head;
    char        *tmp;

    head = *(env);
    key[ft_strlen(key) - 1] = 0;
    while (*(env) && ft_strncmp((*env)->key, key, ft_strlen(key)))
        *(env) = (*env)->next;
    tmp = sh_format_env_var(*env, 0, 0);
    tmp = ft_strjoin(tmp, val, NULL, 0b11);
    sh_update_env(&head, key, tmp);
    *(env) = head;
}