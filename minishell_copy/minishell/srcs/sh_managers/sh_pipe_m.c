#include "../../includes/minishell.h"

/**
 * @brief Initializes a new pipe node
 * 
 * Creates a new pipe and allocates a node to manage it
 * 
 * @return Newly allocated pipe node or NULL if allocation fails
 */
t_sh_pipe *sh_init_pipe(void)
{
  t_sh_pipe *new_pipe;

  // allocate memory for new pipe node
  new_pipe = malloc(sizeof(t_sh_pipe));
  if (!new_pipe)
    return(NULL);
  // initialize fd to invalid state
  new_pipe->fds[0] = -1;
  new_pipe->fds[1] = -1;
  // create pipe
  if (pipe(new_pipe->fds) == -1)
  {
    // cleanup on pipe creation failure
    free(new_pipe);
    return(NULL);
  }
  // initialize next pointer
  new_pipe->next = NULL;
  return (new_pipe);
}
/**
 * @brief Pushes a pipe node to the top of a stack
 * 
 * Adds a new pipe node to the beginning of the list
 * 
 * @param head Pointer to the head of the pipe list
 * @param top Node to be added to the top of the list
 */
void sh_pipe_push(t_sh_pipe **head, t_sh_pipe *top)
{
  // validate input pointer
  if(!head || !top)
    return;
  // if list is empty set new node as head 
  if (!*head)
  {
    *head = top;
    return;
  }
  top->next = *head;
  *head = top;
}

/**
 * @brief Removes and returns the top pipe node
 * 
 * Pops the first node from the pipe list
 * 
 * @param head Pointer to the head of the pipe list
 * @return Removed pipe node
 */
t_sh_pipe *sh_pipe_pop(t_sh_pipe **head)
{
  t_sh_pipe *tmp;

  // validate input pointers
  if (!head|| !*head)
    return(NULL);
  // store current head
  tmp = *head;
  // move head to next node
  *head =(*head)->next;
  // detach popped node from list
  tmp->next = NULL;
  return(tmp);
}
/**
 * @brief Deletes a single pipe node
 * 
 * Closes pipe file descriptors and frees the node
 * 
 * @param pipe_node Pipe node to be deleted
 */
void sh_delete_pipe(t_sh_pipe *pipe_node)
{
    // close read fd if valid
    if (pipe_node->fds[0] > STDERR_FILENO)
        close(pipe_node->fds[0]);

    // close write fd if valid
    if (pipe_node->fds[1] > STDERR_FILENO)
        close(pipe_node->fds[1]);

    // free the pipe node
    free(pipe_node);
}

