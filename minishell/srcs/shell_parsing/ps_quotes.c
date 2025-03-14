#include "../../includes/minishell.h"

extern int g_exit_code;

void enforce_quotes(char **line, int tmp_fd, t_qstate state)
{
    char *orig;
    char *dq_buf;

    if (!*line)
        return;
    orig = *line;
    set_dq_holder(*line, 0);
    while (**line)
        update_quote_state(*((*line)++), &state);
    if (state)
    {
        dq_buf = open_dq_file(tmp_fd, state);
        if (!dq_buf)
        {
            free(dq_buf);
            *line = orig;
            return;
        }
        dq_buf = join_str(orig, dq_buf, "\n", 0b11);
        enforce_quotes(&dq_buf, tmp_fd, QU_ZERO);
        set_dq_holder(dq_buf, 0);
        *line = dq_buf;
        return;
    }
    *line = orig;
}

t_qstate    quote_error(char *line, char *end_marker, t_qstate state)
{
    while (*line)
        update_quote_state(*(line++), &state);
    if (end_marker && state == QU_SINGLE)
        *end_marker = '\'';
    else if (end_marker && state == QU_DOUBLE)
        *end_marker = '"';
    return state;
}

void remove_quotes(char **line, t_qstate state)
{
    char *ptr;
    char *result;
    char *res_ptr;

    ptr = *line;
    result = malloc((dq_strlen(*line) + 1) * sizeof(char));
    if (!result)
        return;
    res_ptr = result;
    while (*ptr)
    {
        if (update_quote_state(*ptr, &state))
        {
            ptr++;
            continue;
        }
        *(res_ptr++) = *(ptr++);
    }
    *res_ptr = '\0';
    free(*line);
    *line = result;
}