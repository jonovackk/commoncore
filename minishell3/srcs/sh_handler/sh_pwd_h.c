#include "../../includes/minishell.h"

extern int  g_exit_code;

char    *trim_pwd(char *str)
{
    char    *last_slash;

    last_slash = ft_strrchr(str, '/');
    if (!last_slash)
        return (ft_strdup(""));
    return (ft_strdup(last_slash));
}

char    *sh_get_pwd(void)
{
    char    cwd[65536];

    if (getcwd(cwd, sizeof(cwd)))
        return (ft_strdup(cwd));
    return (NULL);
}

int     pwd_builtin(t_sh_cmd *cmd)
{
    char    cwd[65536];

    if (getcwd(cwd, sizeof(cwd)))
        ft_dprintf(cmd->outfile, "%s\n", cwd);
    else
    {
        perror("getcwd() error");
        return (ERR_FAIL);
    }
    return (ERR_NONE);
}

char    *get_prompt_str(t_sh_env *envp)
{
    static  t_sh_env *saved_env = NULL;
    char    *prompt;
    char    *pwd;

    if (envp)
        saved_env = envp;
    if (sh_find_env(saved_env, "PWD"))
    {
        pwd = trim_pwd(sh_find_env(saved_env, "PWD")->values[0]);
        pwd = ft_strjoin(pwd, " ~ ", 0, 0b01);
    }
    else
        pwd = ft_strdup(" ~ ");
    if (!g_exit_code)
        prompt = ft_strjoin(P_SUCCESS, P_TAIL, 0, 0b00);
    else
        prompt = ft_strjoin(P_FAIL, P_TAIL, 0, 0b00);
    prompt = ft_strjoin(prompt, pwd, 0, 3);
    return (prompt);
}