/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_node_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:12 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:07:13 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    sh_set_parent_node(t_sh_node **root, t_sh_node *new_parent, int pos)
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

void    sh_set_child_node(t_sh_node **root, t_sh_node *child, int pos)
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

void    sh_connect_nodes(t_sh_node **root, t_sh_node *sibling, t_sh_cmd *cmd, t_sh_token *tok)
{
    if (!root || !sibling)
        return;
    if (!(*root))
    {
        *root = sibling;
        return;
    }
    sh_set_parent_node(root, sh_create_exec_node(cmd, tok), LEFT);
    sh_set_child_node(root, sibling, RIGHT);
}

void    sh_destroy_node(t_sh_node *node)
{
    if (!node)
        return;
    if (node->token)
        sh_token_free(node->token);
    if (node->cmd)
        sh_free_cmd(node->cmd);
    free(node);
}

void        sh_destroy_tree(t_sh_node *node)
{
    if (!node)
        return;
    sh_destroy_tree(node->left);
    sh_destroy_tree(node->right);
    if (node->token)
        sh_token_free(node->token);
    if (node->cmd)
        sh_free_cmd(node->cmd);
    free(node);
}