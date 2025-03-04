#include "../../includes/minishell.h"

t_variable  *get_variable(t_variable *vars, char *name)
{
    while (vars && ft_strncmp(vars->name, name, ft_strlen(vars->name) +1))
        vars = vars->next;
    return (vars);
}

t_variable  *get_last_variable(t_variable *vars)
{
    while (vars->next)
        vars = vars->next;
    return (vars);
}

void    set_variable(t_variable **vars, char *name, char *value)
{
    t_variable  *head;

    head = *vars;
    while (*vars && ft_strncmp((*vars)->name, name, ft_strlen(name)))
        *vars = (*vars)->next;
    if (!(*vars))
    {
        add_variable(&head, create_variable(name));
        *vars = get_last_variable(head);
    }
    ft_free_tab((void **)(*vars)->values);
    (*vars)->values = NULL;
    (*vars)->values = ft_split(value, ';');
    *vars = head;
    if (ft_strlen(value))
        free(value);
}

void    append_variable(t_variable **vars, char *name, char *value)
{
    t_variable  *head;
    char        *tmp;

    head = *vars;
    name[ft_strlen(name) - 1] = 0;
    while (*vars && ft_strncmp((*vars)->name, name, ft_strlen(name)))
        *vars = (*vars)->next;
    tmp = get_variable_string(*vars, 0, 0);
    tmp = ft_strjoin(tmp, value, NULL, 0b11);
    set_variable(&head, name, tmp);
    *vars = head;
}