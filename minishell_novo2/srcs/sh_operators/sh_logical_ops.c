#include "../../includes/minishell.h"

/**
 * @brief Waits for and processes logical AND/OR operation processes
 * 
 * Handles waiting for child processes and extracting exit status
 * 
 * @param executor Execution context containing process list
 * @return Exit code of the processed process
 */
int sh_wait_logical_operation(t_sh_exec *executor)
{
  t_sh_pid *process_to_wait;
  int exit_code;

  // pop process from list
  process_to_wait= sh_pid_pop(&(executor->running_procs));
  exit_code = 0;
  if(process_to_wait)
  {
    // close pipe resources
    sh_cleanup_pipes(executor->active_pipes);
    // wait for process and process its exit
    waitpid(process_to_wait->pid, &exit_code, 0);
    sh_process_command_exit(exit_code);
    // extract actual exit code status
    exit_code = WEXITSTATUS(exit_code);
  }
  else
    //use global exit status if no process
    exit_code = g_shell_exit_status;
  // free process node
  free(process_to_wait);
  return(exit_code);
}
/**
 * @brief Executes logical AND operation
 * 
 * Runs left and right side of AND operation based on previous command's success
 * 
 * @param tree Execution tree node
 * @param node_fd File descriptors for input/output
 * @param executor Execution context
 * @return Exit status of the operation
 */
int sh_execute_logical_and(t_sh_node *tree, int *node_fd, t_sh_exec *executor)
{
  int exit_code;

  // redirect input if needed
  if (node_fd[0] != STDERR_FILENO)
    dup2(node_fd[0], STDIN_FILENO);
  // execute left side of AND
  sh_execute_command_multiplex(tree->left, node_fd, executor, EXEC_WAIT);
  exit_code = sh_wait_logical_operation(executor);
  g_shell_exit_status = exit_code;
  // if left side succeeds, execute right side
  if (exit_code == ERR_NONE)
  {
    sh_execute_command_multiplex(tree->right, node_fd, executor, EXEC_WAIT);
    g_shell_exit_status = sh_wait_logical_operation(executor);
  }
  return(g_shell_exit_status);
}
/**
 * @brief Executes logical OR operation
 * 
 * Runs left and right side of OR operation based on previous command's failure
 * 
 * @param tree Execution tree node
 * @param node_fd File descriptors for input/output
 * @param executor Execution context
 * @return Exit status of the operation
 */
int sh_execute_logical_or(t_sh_node *tree, int *node_fd, t_sh_exec *executor)
{
    int exit_code;

    // redirect input if needed
    if (node_fd[0] != STDIN_FILENO)
        dup2(node_fd[0], STDIN_FILENO);
    // execute left side of OR
    sh_execute_command_multiplex(tree->left, node_fd, executor, EXEC_WAIT);
    // wait and get exit code
    exit_code = sh_wait_logical_operation(executor);
    g_shell_exit_status = exit_code;
    // iff left side fails, execute right side
    if (exit_code != ERR_NONE)
    {
        sh_execute_command_multiplex(tree->right, node_fd, executor, EXEC_WAIT);
        g_shell_exit_status = sh_wait_logical_operation(executor);
    }
    return (g_shell_exit_status);
}