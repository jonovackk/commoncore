#include "../../includes/minishell.h"

void    add_variable(t_variable **variables, t_variable *variable)
{
    t_variable  *temp;

    if (!variables || !variable)
        return;
    if (!(*variables))
    {
        *variables = variable;
        return;
    }
    temp = *variables;
    while (temp->next)
        temp = temp->next;
    temp->next = variable;
}

void    remove_variable(t_variable **variables, char *name)
{
    t_variable  *prev;
    t_variable  *current;
    t_variable  *head;

    current = *variables;
    prev = current;
    head = NULL;
    while (current && ft_strcmp(current->name, name))
    {
        prev = current;
        current = current->next;
    }
    if (prev == current)
        head = current->next;
    if (current && prev)
    {
        prev->next = current->next;
        delete_variable(current);
    }
    if (head)
        *variables = head;
}

void    delete_variable(t_variable *variable)
{
    free(variable->name);
    if (variable->values && *(variable->values))
        ft_free_tab((void **) variable->values);
    else
        free(variable->values);
    free(variable);
}

void    clear_variables(t_variable *variables)
{
    t_variable  *temp;

    while (variables)
    {
        temp = variables->next;
        delete_variable(variables);
        variables = temp;
    }
}

