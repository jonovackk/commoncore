#include "../../includes/minishell.h"

int     check_subtoken_validity(t_sh_token *token)
{
    t_token_kind    binop_mask;
    t_token_kind    str_mask;

    binop_mask = TOKEN_LOGICAL | TOKEN_PIPE;
    str_mask = TOKEN_TEXT | TOKEN_REDIRECT;
    if ((token->type & TOKEN_LOGICAL) && (token->next->type & binop_mask ))
        return (0);
    else if (token->type == TOKEN_REDIRECT )
}

