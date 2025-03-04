/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builders.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:25:32 by jnovack           #+#    #+#             */
/*   Updated: 2025/03/04 14:53:50 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_variable  *create_variable(char *input)
{
    t_variable  *var;
    char        *equal_sign;
    char        **parts;

    var = malloc(sizeof(t_variable));
    if (!var)
        return(NULL);
    equal_sign = ft_strchr(input, '=');
    if (equal_sign)
    {
        parts = ft_split(input, '=');
        var->name = ft_strdup(parts[0]);
        ft_free_tab((void **)parts);
        var-values = ft_split(equal_sign + 1, ':');
    }
    else
    {
        var->name = ft_strdup(input);
        var->values = NULL;   
    }
    var->next = NULL;
    return (var);
}

t_instruction   *create_instruction(t_redirect *redirections, char **arguments, t_variable **env_vars)
{
    t_instruction   *instruction;

    intruction = malloc(sizeof(t_instruction));
    if (!instruction)
        return (NULL);
    instruction->in_fd = 0;
    instruction->out_fd = 1;
    instruction->heredoc_fd = -42;
    instruction->cmd_path = NULL;
    if (arguments)
        instruction->cmd_path = ft_get_path(*arguments, *env_vars);
    instruction->arguments = arguments;
    instruction->env_vars = env_vars;
    return (instruction);
}

t_tree_node *create_tree_node(t_instruction *instruction, t_lex *lexeme)
{
    t_tree_node *node;

    node = malloc(sizeof(t_tree_node));
    if (!node)
        return (NULL);
    node->instruction =instruction;
    node->lexeme = lexeme;
    node->left_child = NULL;
    node->right_child = NULL;
    return (node);
}

t_lex   *create_lexeme(char *content, t_lex_type lex_type)
{
    t_lex   *lexeme;

    lexeme = malloc(sizeof(t_lex));
    if (!lexeme)
        return (NULL);
    lexeme->str = content;
    lexeme->type = lex_type;
    lexeme->next = NULL;
    lexeme->prev = NULL;
    return (lexeme);
}




