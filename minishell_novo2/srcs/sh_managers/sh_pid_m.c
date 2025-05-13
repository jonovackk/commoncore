/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pid_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:16 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:07:17 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Initializes a new process ID node
 * 
 * Creates a new node for tracking process IDs
 * 
 * @param pid Process ID to store
 * @return Newly allocated process ID node
 */
t_sh_pid *sh_init_pid(pid_t pid)
{
  t_sh_pid *new_pid;

  //alocates memory for the new PID node
  new_pid = malloc(sizeof(t_sh_pid));
  if(!new_pid)
    return(NULL);
  // set process if and initialize next pointer
  new_pid->pid = pid;
  new_pid->next = NULL;
  return(new_pid);
}

/**
 * @brief Pushes a process ID node to the top of a stack
 * 
 * Adds a new process ID node to the beginning of the list
 * 
 * @param head Pointer to the head of the process ID list
 * @param top Node to be added to the top of the list
 */
void sh_pid_push(t_sh_pid **head, t_sh_pid *top)
{
  // calidate input pointer
  if (!head || !top)
    return;
  // if list is empty set new node as head
  if (!*head)
  {
    *head = top;
    return;
  }
  // insert new node at the beginning of the list
  top->next = *head;
  *head = top;
}

/**
 * @brief Removes and returns the top process ID node
 * 
 * Pops the first node from the process ID list
 * 
 * @param head Pointer to the head of the process ID list
 * @return Removed process ID node
 */
t_sh_pid *sh_pid_pop(t_sh_pid **head)
{
  t_sh_pid *tmp;

  // validate input pointers
  if (!head || !*head)
    return(NULL);
  // store current head
  tmp = *head;
  // move head to next node
  *head = (*head)->next;
  // detach popped node from list
  tmp->next = NULL;
  return(tmp);
}
/**
 * @brief Recursively deletes a list of process ID nodes
 * 
 * Frees all nodes in the process ID list
 * 
 * @param pid_list Head of the process ID list to delete
 */
void sh_delete_pid_list(t_sh_pid *pid_list)
{
    // base case: empty list
    if (!pid_list)
        return;

    // recursively delete rest of the list
    sh_delete_pid_list(pid_list->next);
    
    // free current node
    free(pid_list);
}