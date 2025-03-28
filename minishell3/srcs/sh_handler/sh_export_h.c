#include "../../includes/minishell.h"

int     export_syntax_valid(char *str)
{
    char    *tmp = str;
    
    if (ft_isdigit(*str) || !*str)
        return (0);
    while (*str && (ft_isalnum(*str) || *str == '_') && *str != '=')
        str++;
    if (*str == '+' && *(str + 1) == '=')
        return (1);
    return ((tmp != str && *str == '=') || !*str);
}

int     show_export_list(t_sh_cmd *cmd)
{
    char        **env_array;
    char        **tmp;
    char        *line;

    env_array = get_env_strings(*(cmd->environment), 1);
    if (!env_array)
        return (ERR_FAIL);
    sort_str_array(env_array, array_len(env_array));
    tmp = env_array;
    while (*tmp)
    {
        if (ft_strncmp(*tmp, "_=", 2))
        {
            line = str_join("declare -x ", *tmp, NULL, 0);
            ft_dprintf(cmd->outfile, "%s\n", line);
            free(line);
        }
        tmp++;
    }
    free_str_array((void **)env_array);
    return (ERR_NONE);
}

int     export_var(t_sh_cmd *cmd, char *tmp)
{
    char        **var = NULL;
    char        *trimmed;

    if (ft_strchr(tmp, '='))
    {
        str_append(&var, ft_strndup(tmp, ft_strcspn(tmp, "=")));
        str_append(&var, ft_strdup(tmp + ft_strlen(*var) + 1));
        trimmed = str_trim(var[1], "\"");
        free(var[1]);
        var[1] = trimmed;
        if (ft_strlen(var[0] && var[0][ft_strlen(var[0]) - 1] == '+'))
            sh_extend_env(cmd->environment, var[0], ft_strdup(var[1]));
        else
        {
            if (var[1])
                sh_update_env(cmd->environment, var[0], ft_strdup(var[1]));
            else
                sh_update_env(cmd->environment, var[0], "");
        }
        free_str_array((void **)var);
    }
    else if (!sh_find_env(*(cmd->environment), tmp))
        sh_update_env(cmd->environment, tmp, NULL);
    return (ERR_NONE);
}

int     export_builtin(t_sh_cmd *cmd)
{
    char        *tmp;
    error_t     errcode;

    tmp = cmd->arguments;
    errcode = ERR_NONE;
    if (array_len(tmp) == 1 && show_export_list(cmd))
        errcode = ERR_FAIL;
    else
    {
        while (*(++tmp))
        {
            if (!export_syntax_valid(*tmp))
            {
                print_error_message(ERR_INV, *tmp);
                errcode = ERR_FAIL;
            }
            if (export_var(cdm, *tmp))
                errcode = ERR_FAIL;
        }
    }
    update_env_context(cmd->environment);
    retunr (errcode);
}