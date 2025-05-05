#include "../../includes/minishell.h"

/**
 * @brief Creates a command node from tokens
 * 
 * What it does:
 * - Parses and processes string and redirection tokens
 * - Collects arguments and redirection operations
 * - Creates a command node from the processed tokens
 * 
 * @param tokens Pointer to the current token pointer (will be updated)
 * @param env The environment variables
 * @param tmp The current token to start processing from
 * @return A new command node with the parsed information
 */
t_sh_node *sh_cmd_token(t_sh_token **tokens, t_sh_env **env, t_sh_token *tmp)
{
    char **args;
    redir_t *redirs;

    args = NULL;
    redirs = NULL;
    while (tmp && (tmp->type & (TOKEN_TEXT | TOKEN_REDIRECT)))
    {
        if (tmp->type & TOKEN_REDIRECT)
        {
            sh_add_redir(&redirs, sh_init_redir(tmp));
            tmp = tmp->next;
        }
        else if (tmp->type & TOKEN_TEXT)
            sh_strapp(&args, ft_strdup(tmp->str));
        tmp = tmp->next;
    }
    *tokens = tmp;
    return (sh_init_sh_node(sh_init_command(redirs, args, env), NULL));
}

/**
 * @brief Processes tokens within parentheses and builds a subtree
 * 
 * What it does:
 * - Builds a subtree from the tokens within parentheses
 * - Tracks nesting level to properly match opening and closing parentheses
 * - Inserts the subtree into the main tree
 * 
 * @param tk Pointer to the current token pointer (will be updated)
 * @param tree Pointer to the current tree node
 * @param env The environment variables
 */
void sh_brace_tree(t_sh_token **tk, t_sh_node **tree, t_sh_env **env)
{
    t_sh_node  *subtree;
    int     level;

    subtree = sh_build_tree((*tk)->next, env);
    level = 0;
    if (!(*tree))
        *tree = subtree;
    else
        sh_insert_child(tree, subtree, RIGHT);
    (*tk) = (*tk)->next;
    while ((*tk) && (!((*tk)->type & TOKEN_PARENTHESIS && \
            !ft_strncmp((*tk)->str, ")", 2)) || level))
    {
        if ((*tk)->type & TOKEN_PARENTHESIS && !ft_strncmp((*tk)->str, "(", 2))
            level++;
        if ((*tk)->type & TOKEN_PARENTHESIS && !ft_strncmp((*tk)->str, ")", 2))
            level--;
        (*tk) = (*tk)->next;
    }
    (*tk) = (*tk)->next;
}

/**
 * @brief Connects operations and builds tree structures
 * 
 * What it does:
 * - For binary operators: creates a subtree and associates it with the current tree
 * - For pipe operators: inserts a parent node for the pipe operation
 * 
 * @param tk Pointer to the current token pointer (will be updated)
 * @param tree Pointer to the current tree node
 * @param env The environment variables
 */
void sh_connect_ops(t_sh_token **tk, t_sh_node **tree, t_sh_env **env)
{
    t_sh_node *next;

    next = NULL;
    if ((*tk)->type & TOKEN_LOGICAL)
    {
        next = sh_build_tree((*tk)->next, env);
        sh_associate(tree, next, NULL, sh_dup_token(*tk));
    }
    else if ((*tk)->type & TK_PIPE)
    {
        sh_insert_parent(tree, sh_init_sh_node(NULL, sh_dup_token(*tk)), LEFT);
        (*tk) = (*tk)->next;
    }
}

/**
 * @brief Builds an abstract syntax tree from tokens
 * 
 * What it does:
 * - Processes tokens in sequence to build a tree representation
 * - Handles parentheses, commands, redirections, and operators
 * - Updates environment variables as needed
 * 
 * @param tokens The token list to process
 * @param env The environment variables
 * @return The root node of the built syntax tree
 */
t_sh_node *sh_build_tree(t_sh_token *tokens, t_sh_env **env)
{
    t_sh_node          *tree;
    t_token_kind        tmp;

    tree = NULL;
    sh_update_env(env);
    while (tokens)
    {
        if (tokens->type & TOKEN_PARENTHESIS)
        {
            if (!ft_strncmp(tokens->str, "(", 2))
                sh_brace_tree(&tokens, &tree, env);
            else
                return (tree);
        }
        else if (tokens->type & (TOKEN_TEXT | TOKEN_REDIRECT))
            sh_insert_child(&tree, sh_cmd_token(&tokens, env, tokens), RIGHT);
        if (!tokens)
            return (tree);
        tmp = tokens->type;
        if (tmp & (TOKEN_LOGICAL | TOKEN_PIPE))
            sh_connect_ops(&tokens, &tree, env);
        if (tmp & TOKEN_LOGICAL)
            return (tree);
    }
    return (tree);
}