#include "../../includes/minishell.h"

int     var_list_size(t_sh_env *env)
{
    int     size = 0;
    while (env)
    {
        size++;
        env = env->next;
    }
    return (size);
}

char    *get_env_string(t_sh_env *env, int format, int include_name)
{
    char    *str = NULL;

    if (env == NULL)
        return (NULL);
    if (!env->values && include_name)
        return (ft_strdup(env->key));
    if (include_name)
        str = str_join(ft_strdu(env->key), "=", NULL, 0b01);
    if (format)
        str = str_join(str, "\"", NULL, 1);
    str = str_join(str, join_str_array(env->values, ":", 0b00), NULL, 0b11);
    if (format)
        str = str_join(str, "\"", NULL, 0b01);
    return (str);
}

char    **get_env_string(t_sh_env *env, int format)
{
    int     i;
    int     size;
    char    **env_array;

    i = -1;
    size = var_list_size(env) + 1;
    env_array = malloc(size * sizeof(char *));
    if (!env_array)
        return (NULL);
    while (++i < size - 1)
    {
        env_array[i] = get_env_strin(env, format, 1);
        if (!env_array[i])
        {
            free_str_array((void **)env_array);
            return (NULL);
        }
        env = env->next;
    }
    env_array[i] = NULL;
    return (env_array);
}

int     env_builtin(t_sh_cmd *cmd)
{
    t_sh_env    *env;
    char        **env_array;
    char        **tmp;

    if (array_len(cmd->arguments) > 1)
    {
        print_error_message(ERR_ARGS, "env");
        return (127);
    }
    env = *(cmd->environment);
    env_array = get_env_string(env, 0);
    if (!env_array)
        return (ERR_FAIL);
    tmp = env_array;
    while (*tmp)
    {
        if (ft_strchr(*tmp, '='))
            ft_dprintf(cmd->outfile, "%s\n", *tmp);
        tmp++;
    }
    free_str_array((void **)env_array);
    return (ERR_NONE);
}