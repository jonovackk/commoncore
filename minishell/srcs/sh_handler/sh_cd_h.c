#include "../../includes/minishell.h"

void    load_directory_env(t_sh_env *envp, t_sh_env **vars)
{
    vars[0] = sh_find_env(envp, "HOME");
    vars[1] = sh_find_env(envp, "OLDPWD");
    vars[2] = sh_find_env(envp, "PWD");
    vars[3] = NULL;
}

error_t     change_directory(const char *target)
{
    if (!target)
        return (ERR_FAIL);
    if (chdir(target) == -1)
    {
        if (errno = EACCES)
            print_error_message(ERR_NOPERM, target);
        else
            print_error_message(ERR_NOENT, target);
        return (ERR_FAIL);
    }
    return (ERR_NONE);
}

error_t     process_cd_args(int argc, char **argv, t_sh_env **vars, int out)
{
    char    *target;

    target = NULL;
    if (!argc)
        target = *(vars[0]->values);
    else if (argc == 1)
    {
        if (!ft_strncmp(argv[0], "~", 2) && vars[0])
            target = *(vars[0]->values);
        else if (!ft_strncmp(argv[0], "-", 2) && vars[1])
        {
            if (vars[1]->values)
            {
                ft_dprintf(out, "\033[37;1m-> %s\033[0m\n", *(vars[1]->values));
                target = *(vars[1]->values);
            }
            else
                print_error_message(ERR_UNSET, "OLDPWD");
        }
        else
            target = argv[0];
    }
    return (change_directory(target));
}

int     cd_builtin(t_sh_cmd *cmd)
{
    int         argc;
    char        *newdir;
    t_sh_env    *vars[4];

    argc = array_len(cmd->arguments);
    if (argc > 2)
        print_error_message(ERR_ARGS, "cd");
    load_directory_env(*(cmd->environment), vars);
    if ((argc - 1) == 0 && !vars[0])
        print_error_message(ERR_UNSET, "HOME");
    else if (process_cd_args(argc -1, cmd->arguments + 1, vars, cmd->outfile))
        return (ERR_FAIL);
    if (vars[2])
        sh_update_env(cmd->environment, "OLDPWD", ft_strdup(vars[2]->values[0]));
    else
        print_error_message(ERR_UNSET, "OLDPWD");
    newdir = sh_get_pwd();
    if (newdir)
        sh_update_env(cmd->environment, "PWD", newdir);
    else
        print_error_message(ERR_UNSET, "PWD");
    return (ERR_NONE);
}