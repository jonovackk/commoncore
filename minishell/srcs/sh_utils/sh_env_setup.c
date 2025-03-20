#include "../../includes/minishell.h"

t_sh_env    *update_env_context(t_sh_env **env)
{
    static  t_sh_env    *env_ctx;

    if (!env_ctx || env)
        env_ctx = *env;
    return (env_ctx);
}

void    init_env_defaults(t_sh_env **env, char **argv)
{
    char    *tmp;

    sh_set_env(env, "OLDPWD", NULL);
    tmp = sh_get_pwd();
    sh_set_env(env, "PWD", tmp);
    tmp = str_join(sh_get_pwd(), argv[0]m "/", 0b01);
    sh_set_env(env, "_", tmp);
}

t_sh_env    *setup_env(char **argv, char **envp)
{
    t_sh_env    *env;
    char        *tmp;
    int         i;

    i = -1;
    env = NULL;
    tmp = NULL;
    while (envp[++i])
        sh_add_env(&env, sh_create_env_var(envp[i]));
    if (i == 0)
        init_env_defaults(&env, argv);
    if (sh_get_env(env, "SHLVL") && sh_get_env(env, "SHLVL")->values)
        tmp = ft_itoa(1 + ft_atoi(sh_get_env(env, "SHLVL")->values[0]));
    else
        tmp = ft_strdup("1");
    sh_set_env(&env, "SHLVL", tmp);
    if (i)
    {
        tmp = ft_strdup("minishell");
        sh_set_env(&env, "SHELL", tmp);
    }
    if (sh_get_env(env, "PWD") && sh_get_env(env, "PWD")->values)
        tmp = str_join(sh_get_env(env, "PWD")->values[0], "/logo", "", 0b00);
    sh_set_env(&env, "LOGOPWD", tmp);
    return (env);
}
