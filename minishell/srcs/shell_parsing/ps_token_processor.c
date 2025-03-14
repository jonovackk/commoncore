#include "../../includes/minishell.h"

int     is_valid_operator(char *input, t_qstate qstat)
{
    char        **current;
    static char *operators[11] = {" ", "(", ")", "||", "&&", \
                                "|", ">>", ">", "<<", "<", NULL};
    current = operators;
    if (!input || !*input)
        return (1);
    if (ft_isspace(*input) && qstat == QT_NONE)
        return (1);
    while (*current && (ft_strncmp(input, *current, ft_strlen(*current)) || qstat != QT_NONE))
        current++;
    return (ft_strlen(*current));
}

t_token_type    get_token_category(char *input, t_qstate qstat)
{
    if (qstat != QT_NONE)
        return (TOKEN_TEXT);
    if (!ft_strncmp(input, "(", 1) || !ft_strncmp(input, ")", 1))
        return (TOKEN_PARENTHESIS);
    if (!ft_strncmp(input, "||", 2) || !ft_strncmp(input, "&&", 2))
        return (TOKEN_LOGICAL);
    if (!ft_strncmp(input, "|", 1))
        return (TOKEN_PIPE);
    if (!ft_strncmp(input, ">", 1) || !ft_strncmp(input, "<", 1))
        return (TOKEN_REDIRECT);
    return (TOKEN_TEXT);
}

t_sh_token     *parse_into_tokens(char *input, t_qstate qstat)
{
    t_sh_token *result;
    char    *token_content;
    char    *current_pos;
    int     token_length;

    result = NULL;
    if (!input || !*input)
        return (NULL);
    current_pos = input;
    token_length = is_valid_operator(current_pos, qstat);
    while (*current_pos && (!token_length || (ft_isspace(*current_pos) && qstat != QT_NONE)))
    {
        update_quote_status(*(current_pos++), &qstat);
        token_length = is_valid_operator(current_pos, qstat);
    }
    if (current_pos == input)
        token_content = ft_strndup(input, token_length);
    else
        token_content = ft_strndup(input, current_pos - input);
    if (ft_strncmp(token_content, " ", 2))
        result = create_token(ft_strdup(token_content), get_token_category(input, qstat));
    append_token(&result, parse_into_tokens(input + ft_strlen(token_content), qstat));
    free(token_content);
    return (result);
}

int     check_for_wildcard(char *input, t_qstate qstat)
{
    char        *current_pos;

    current_pos = input;
    while (*current_pos)
    {
        update_quote_status(*current_pos, &qstat);
        if (*current_pos == '*' && qstat == QT_NONE)
            return (1);
        current_pos++;
    }
    return (0);
}

void        procees_home_expansion(t_sh_token **token_list, t_envvar *home_var)
{
    t_sh_token  *current;

    current = *token_list;
    while (current)
    {
        if (!ft_strncmp(current->str, "~", 2))
        {
            if (home_var)
            {
                free(current->str);
                current->str = get_environment_value(home_var, 0, 0);
            }
            current = current->next;
        }
        else
            current = current->next;
    }
}