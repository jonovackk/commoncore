#include "../../includes/minishell.h"

void    attach_parent(t_sh_node **root, t_sh_node *new_parent, int pos)
{
    if (!root || !new_parent)
        return;
    if (!(*root))
    {
        *root = new_parent;
            return;
    }
    if (pos == LEFT)
        new_parent->left = *root;
    else
        new_parent->right = *root;
    *root = new_parent;
}

void    attach_child(t_sh_node **root, t_sh_node *child, int pos)
{
    if (!root)
        return;
    if (!(*root))
    {
        *root = child;
        return;
    }
    if (pos == LEFT)
        (*root)->left = child;
    else
        (*root)->right = child;
}

void    merge_nodes(t_sh_node **root, t_sh_node *sibling, t_sh_cmd *cmd, t_sh_token *tok)
{
    if (!root || !sibling)
        return;
    if (!(*root))
    {
        *root = sibling;
        return;
    }
    attach_parent(root, make_node(cmd, tok), LEFT);
    attach_child(root, sibling, RIGHT);
}

void        delete_node(t_sh_node *node)
{
    if (!node)
        return;
    if (node->token)
        delete_token(node->token);
    if (node->command)
        delete_command(node->command);
    free(node);
}

void        clear_tree(t_sh_node *node)
{
    if (!node)
        return;
    clear_tree(node->left);
    clean_tree(node->right);
    if (node->token)
        delete_token(node->token);
    if (node->command)
        delete_command(node->command);
    free(node);
}