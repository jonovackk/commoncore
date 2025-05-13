/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_closers_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:32 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:07:33 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Closes multiple file descriptors
 * 
 * Variadic function to close a specified number of file descriptors
 * 
 * @param count Number of additional file descriptors to close
 * @param fd First file descriptor to close
 * @param ... Variable number of additional file descriptors
 */

void sh_close_multiple_fd(int count, int fd, ...)
{
  va_list files;
  int current_fd;
  int i;

  i = 0;
  // close the 1st fd
  close (fd);
  // initialize var arg list
  va_start(files, fd);
  // close additional fd
  while (i++ < count)
  {
    current_fd = va_arg(files, int);
    if (current_fd >= 0)
      close (current_fd);
  }
  // clean up var arg list
  va_end(files);
}

/**
 * @brief Closes file descriptors associated with a command
 * 
 * Safely closes input, output, and heredoc file descriptors
 * 
 * @param cmd Command with file descriptors to close
 */
void sh_cmd_cleanup(t_sh_cmd *cmd)
{
  if (!cmd)
    return;
  // close input fd if valid
  if (cmd->input_fd > STDERR_FILENO)
    close(cmd->input_fd);
  //close output fd if valid
  if (cmd->output_fd > STDERR_FILENO)
    close (cmd->output_fd);
  // clsoe heredoc fd if valid
  if (cmd->heredoc_fd > STDERR_FILENO)
    close (cmd->heredoc_fd);
}
/**
 * @brief Recursively closes file descriptors in an execution tree
 * 
 * Traverses the tree and closes command-associated file descriptors
 * 
 * @param tree Root of the execution tree
 */
void sh_tree_fd_cleanup(t_sh_node *tree)
{
  if (!tree)
    return;
  // recursevely close left subtree
  if (tree->left)
    sh_tree_fd_cleanup(tree->left);
    // recursevely close right subtree
  if (tree->right)
    sh_tree_fd_cleanup(tree->right);
  if (tree->cmd)
    sh_cmd_cleanup(tree->cmd);
}
/**
 * @brief Closes resources in an executor
 * 
 * Closes pipe and process file descriptors, frees associated memory
 * 
 * @param executor Execution context to clean up
 */
void sh_exec_release(t_sh_exec *executor)
{
  t_sh_pipe *current_pipe;
  t_sh_pid *current_pid;

  if (!executor)
    return;
  // close and free pipe fd
  while (executor->active_pipes)
  {
    current_pipe = sh_pipe_pop(&(executor->active_pipes));
    if(current_pipe->fds[0] > STDERR_FILENO)
      close (current_pipe->fds[0]);
    if(current_pipe->fds[1] > STDERR_FILENO)
      close (current_pipe->fds[1]);
    free (current_pipe);
  }
  // free process ids
  while (executor->running_procs)
  {
    current_pid = sh_pid_pop(&(executor->running_procs));
    free (current_pid);
  }
}
/**
 * @brief Closes pipe file descriptors
 * 
 * Iterates through a list of pipes and closes their file descriptors
 * 
 * @param pipes List of pipes to close
 */
void sh_cleanup_pipes(t_sh_pipe *pipes)
{
  if (!pipes)
    return;
  while (pipes)
  {
    if (pipes->fds[0] > STDERR_FILENO)
      close (pipes->fds[0]);
    if (pipes->fds[1] > STDERR_FILENO)
      close (pipes->fds[1]);
    pipes = pipes->next;
  }
}
