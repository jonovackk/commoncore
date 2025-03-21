#include "../../includes/minishell.h"

extern int g_exit_code;

int     calc_var_length(char *str)
{
    char    *ptr;

    ptr = str + 1;
    if (!*ptr)
        return (1);
    if (ft_isdigit(*ptr) || ft_strchr("\"'", *ptr))
        return (2);
    if (!ft_strchr("_?", *ptr) && !ft_isalnum(*ptr))
        return (1);
    if (*ptr == '?')
        return (2);
    ptr++;
    while (*ptr && (ft_isalnum(*ptr) && !ft_strchr("_?", *ptr)))
        ptr++;
    return (ptr - str);
}

void    skip_quotes(char **s, int *rem, t_qstate *state)
{
    while (*s && **s && ((*rem) > 0))
    {
        ft_qs_update(*((*s)++), state);
        (*rem)--;
    }
}

void    insert_env_variable(t_sh_env *env, char *s, char ***res_parts, t_qstate state)
{
    t_sh_env    *env_var;
    char        *key;
    int         key_len;

    (void) state;
    if (*s && *(s + 1) == '?')
    {
        ft_strapp(res_parts, ft_itoa(g_exit_code));
        return;
    }
    s++;
    if (ft_isdigit(*s))
        return;
    key_len = calc_var_length(s - 1);
    if (ft_strchr("\"'", *s))
        ft_strapp(res_parts, ft_strndups(s - 1, 2));
    if (ft_strchr("\"'", *s))
        return;
    key = ft_strndup(s, key_len - 1);
    env_var = sh_find_env(env, key);
    if (!env_var)
        ft_strapp(res_parts, ft_strdup(""));
    else
        ft_strapp(res_parts, ft_get_env_value(env_var, 0, 0));
    free(key);
}

void    replace_env_vars(t_sh_env *env, char **line, t_qstate state)
{
    int     seg_len;
    char    *ptr;
    char    **parts;

    ptr = *line;
    parts = NULL;
    if (!ptr)
        return;
    while (*ptr)
    {
        seg_len = ft_strcspn(ptr, "$");
        ft_strapp(&parts, ft_strndup(ptr, seg_len));
        skip_quotes(&ptr, &seg_len, &state);
        if (!*ptr)
            break;
        if (state != QT_SINGLE && calc_var_length(ptr) > 1)
            insert_env_variable(env, ptr, &parts, state);
        else
            ft_strapp(&parts, ft_strndup(ptr, calc_var_length(ptr)));
        ptr += calc_var_length(ptr);
    }
    free(*line);
    *line = ft_strsjoin(parts, NULL, 0b01);
}