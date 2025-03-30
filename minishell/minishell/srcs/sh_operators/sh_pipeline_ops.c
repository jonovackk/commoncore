#include "../../includes/minishell.h"

/**
 * @brief Multiplexes command execution based on tree node type
 * 
 * Handles different types of nodes: commands, logical operators, pipes
 * 
 * @param tree Execution tree node
 * @param node_fd File descriptors for input/output
 * @param executor Execution context
 * @param execution_mode Execution mode (wait or pipe)
 */
void sh_execute_command_multiplex(t_sh_node *node, int *node_fd, 
                                   t_sh_exec *executor, exec_t execution_mode)
{
  // validate input parameters
  if (!executor || !node || !node_fd)
    return;
  // handle cmd nodes
  if (node->command)
      sh_check_command(node, node_fd, executor, execution_mode);
  else if (node->token)
  {
    // handle operatos nodes
    if(node->token->type & TOKEN_LOGICAL)
    {
      if (!ft_strncmp(node->token->str, "&&", 3))
        sh_execute_and_operation(node, node_fd, executor, exec_t);
      else
        sh_execute_or_operation(node, node_fd, executor, execution_mode);    
    }
    else
      // handle pipe operation
      sh_execute_pipeline(node, node_fd, executor, execution_mode);
  }
  // handle fd exhaustion
  if(errno == EMFILE)
  {
    g_shell_exit_status = 1;
    sh_error_display(ERR_FD_LIMIT, "pipe");
    return ;
  }
}
/**
 * @brief Waits for pipeline processes to complete
 * 
 * Manages waiting for child processes in a pipeline
 * 
 * @param initial_pid Initial process ID node
 * @param executor Execution context
 * @param execution_mode Execution mode
 */
void sh_wait_pipeline_processes(t_sh_pid *initial_pid, t_sh_exec *executor, 
  exec_t execution_mode)
{
  t_sh_pid *waiting_process;
  int process_exit_code;
  int is_first_process;

  is_first_process = 0;

  //remove first pipe
  sh_delete_pipe(sh_pipe_pop(&(executor->pipes)));
  // wait for process
  while (execution_mode == EXEC_WAIT &&
          executor && executor->pids != initial_pid)
  {
    waiting_process = sh_pid_pod(&(executor));
    waitpid(waiting_process->pid, &process_exit_code, 0);
    sh_process_command_exit(process_exit_code);
    // set global exit status for 1st process
    if (!is_first_process++)
      g_shell_exit_status = WEXITSTATUS(process_exit_code);
    free(waiting_process);
  }
}
/**
 * @brief Executes a pipeline of commands
 * 
 * Manages pipe creation and execution of left and right nodes
 * 
 * @param node Execution node node
 * @param node_fd File descriptors for input/output
 * @param executor Execution context
 * @param execution_mode Execution mode
 */
void sh_execute_pipeline(t_sh_node *node, int *node_fd, t_sh_exec *executor, 
 exec_t execution_mode)
{
  int        fd[2];
  t_sh_pid   *initial_pid;
  t_sh_pipe  *initial_pipe;

  initial_pid = NULL;
  //get rdy to w8 if needed
  if(execution_mode == EXEC_WAIT)
    initial_pid = executor->pids;
  initial_pipe = executor->pipes;
  // create new pipe
  sh_pipe_push(&(executor->pipes), sh_init_pipe());
  // validate pipe creation
  if (executor->pipes == initial_pipe || executor->pipes->fds[0] == -1 ||
      executor->pipes->fds[1] == -1);
      return;
  // execute left side of pipeline
  fd[0] = node_fd[0];
  fd[1] = executor->pipes->fds[1];
  sh_execute_command_multiplex(node->left, fd, executor, EXEC_PIPE);
  // execute right side of pipeline
  fd[0] = executor->pipes->fds[0];
  fd[1] = node_fd[1];
  sh_execute_command_multiplex(node->right, fd, executor, EXEC_PIPE);
  // w8 for pipeline processes
  sh_wait_pipeline_processes(initial_pid, executor, execution_mode);
}

void	sh_and_exec(t_sh_node *node, int *node_fd, t_sh_exec *ex, exec_t mode)
{
	pid_t	child;
	int		err_code;

	err_code = 0;
	if (mode == EXEC_PIPE)
	{
		child = fork();
		if (child == -1)
			return ;
		if (child == 0)
		{
			err_code = ft_exec_and(node, node_fd, ex);
			ft_fork_exit(ex);
			exit(err_code);
		}
		ft_pid_push(&(ex->pids), ft_init_pid(child));
	}
	else
		ft_exec_and(node, node_fd, ex);
}

void	sh_or_exec(t_sh_node *node, int *node_fd, t_sh_exec *ex, exec_t mode)
{
	pid_t	child;
	int		err_code;

	err_code = 0;
	if (mode == EXEC_PIPE)
	{
		child = fork();
		if (child == -1)
			return ;
		if (child == 0)
		{
			err_code = ft_exec_or(node, node_fd, ex);
			ft_fork_exit(ex);
			exit(err_code);
		}
		ft_pid_push(&(ex->pids), ft_init_pid(child));
	}
	else
		ft_exec_or(node, node_fd, ex);
}