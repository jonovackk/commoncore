#include "../../includes/minishell.h"

int     check_subtoken_validity(t_sh_token *token)
{
    t_token_kind    binop_mask;
    t_token_kind    str_mask;

    binop_mask = TOKEN_LOGICAL | TOKEN_PIPE;
    str_mask = TOKEN_TEXT | TOKEN_REDIRECT;
    if ((token->type & TOKEN_LOGICAL) && (token->next->type & binop_mask ))
        return (0);
    else if (token->type == TOKEN_REDIRECT && !(token->next->type & logical_mask))
        return (0);
    else if (token->type == TOKEN_PIPE && (token->next->type & logical_mask))
        return (0);
    else if (!ft_strncmp(token->str, "(", 2) &&
        ((token->next->type & logical_mask) || !ft_strncmp(token->next->str, ")", 2)))
        return (0);
    else if (token->type == TOKEN_TEXT && (token->next->type & TOKEN_PARENTHESIS) &&
        !ft_strncmp(token->next->str, "(", 2))
        return (0);
    else if (!ft_strncmp(token->str, ")", 2) &&
        (token->next->type & text_mask || !ft_strncmp(token->next->str, "(", 2)))
        return (0);
    return (1);
    }

int     validate_token_sequence(t_sh_token *token, char **err_token)
{
    if (token->type & (TOKEN_LOGICAL | TOKEN_PIPE))
        return (0);
    while (token->next)
    {
        *err_token = token->next->str;
        if (!check_subtoken_validity(token))
            return (0);
        token = token->next;
    }
    return (token->type & (TOKEN_PARENTHESIS | TOKEN_TEXT));
}
int     check_bracket_balance(t_token *tokens)
{
    int     balance;

    balance = 0;
    while (tokens != NULL)
    {
        if ((tokens->type & TOKEN_PARENTHESIS) && !ft_strncmp(tokens->str, "(", 2))
            balance++;
        else if ((tokens->type & TOKEN_PARENTHESIS) && !ft_strncmp(tokens->str, ")", 2))
            balance--;
        if (balance < 0)
            return (0);
        tokens = tokens->next;
    }
    return (balance == 0);
}

int     verify_tokens(t_token *tokens, char **err_token)
{
    t_sh_token  *current;
    int         here_doc_count;

    *err_token = tokens->str;
    if (!validate_token_sequence(tokens, err_token) || !check_bracket_balance(tokens))
        return (ERR_FAILED);
    current = tokens;
    here_doc_count = 0;
    while (current)
    {
        here_doc_count += ((current->type & TOKEN_REDIRECT) && !ft_strncmp(current->str, "<<", 3));
        current = current->next;
    }
    if (here_doc_count > 16)
        return (0b100);
    return (ERR_NOERRS);
}

int     validate_binop_in_brackets(t_sh_token *token)
{
    int     valid;
    int     bracket_level;

    bracket_level = 0;
    valid = 0;
    if (!token || !(token->type & TOKEN_PARENTHESIS && !ft_strncmp(token->str, "(", 2)))
        return (1);
    token = token->next;
    while (token && (!(token->type & TOKEN_PARENTHESIS && !ft_strncmp(token->str, ")", 2)) || bracket_level))
    {
        if (token->type & TOKEN_PARENTHESIS && !ft_strncmp(token->str, "(", 2))
            bracket_level++;
        if (token->type & TOKEN_PARENTHESIS && ! ft_strncmp(token->str, ")", 2))
            bracket_level--;
        if (!bracket_level && (token->type & TOKEN_LOGICAL))
            valid = 1;
        token = token->next;
    }
    if (!token)
        return (1);
    if (!(token && valid))
        ft_remove_token(&token);
    return (token && valid);
}
