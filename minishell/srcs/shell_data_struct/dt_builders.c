#include "../../includes/minishell.h"

t_sh_env *sh_create_env_var(char *input)
{
    t_sh_env   *new_env;
    char       *equal_sign;
    char       **parts;

    new_env = malloc(sizeof(t_sh_env));
    if (!new_env)
        return (NULL);
    equal_sign = ft_strchr(input, '=');
    if (equal_sign)
    {
        parts = ft_split(input, '=');
        new_env->key = ft_strdup(parts[0]);
        ft_free_tab((void **)parts);
        new_env->values = ft_split(equal_sign + 1, ':');
    }
    else
    {
        new_env->key = ft_strdup(input);
        new_env->values = NULL;
    }
    new_env->next = NULL;
    return (new_env);
}

t_sh_cmd *sh_create_command(t_sh_redir *redirects, char **args, t_sh_env **env)
{
    t_sh_cmd   *cmd;

    cmd = malloc(sizeof(t_sh_cmd));
    if (!cmd)
        return (NULL);
    cmd->input_fd = 0;
    cmd->output_fd = 1;
    cmd->heredoc_fd = -42;
    cmd->redirects = redirects;
    cmd->executable = NULL;
    if (args)
        cmd->executable = sh_get_path(*args, *env);
    cmd->arguments = args;
    cmd->environment = env;
    return (cmd);
}

t_sh_node *sh_create_exec_node(t_sh_cmd *cmd, t_sh_token *token)
{
    t_sh_node   *node;

    node = malloc(sizeof(t_sh_node));
    if (!node)
        return (NULL);
    node->command = cmd;
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

t_sh_token *sh_create_token(char **text, t_token_kind kind)
{
    t_sh_token  *token;

    token = malloc(sizeof(t_sh_token));
    if (!token)
        return (NULL);
    token->content = *text;
    token->type = kind;
    token->next = NULL;
    token->prev = NULL;
    return (token);
}
