#include "../../includes/minishell.h"

int     update_quote_status(char c, t_qstate *qstatus)
{
    t_qstate  previous;

    previous = *qstatus;
    if (*qstatus == QT_NONE)
    {
        if (c == '\'')
            *qstatus = QT_SINGLE;
        if (c == '"')
            *qstatus = QT_DOUBLE;
    }
    else if ((c == '\'' && *qstatus == QT_SINGLE) || (c == '"' && *qstatus == QT_DOUBLE))
        *qstatus = QT_NONE;
    return (*qstatus != previous);
}

int     count_chars_without_quotes(char *str)
{
    t_qstate  qstatus;
    int             length;

    qstatus = QT_NONE;
    length = 0;
    while (*str)
    {
        if (!update_quote_status(*(str++), &qstatus))
            length++;
    }
    return (length);
}

void    clean_patenthesis_tokens(t_sh_token **tokens)
{
    t_sh_token  *current;

    current = *tokens;
    while (current)
    {
        if (!check_valid_logical_parenthesis(current))
        {
            delet_token(&current);
            if (!current)
            {
                *tokens = NULL;
                continue;
            }
            if (!current->prev)
                *tokens = current;
            continue;
        }
        current = current->next;
    }
}