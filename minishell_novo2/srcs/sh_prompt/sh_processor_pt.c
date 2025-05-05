#include "../../includes/minishell.h"

// Global variable to track the last command's exit status
extern int g_shell_exit_status;

/**
 * @brief Handles the interactive prompt and input line
 * 
 * Core responsibilities:
 * 1. Generate and display prompt
 * 2. Read user input
 * 3. Validate input
 * 4. Handle quote-related processing
 * 5. Manage signal states
 * 
 * @return Error status of prompt processing
 */
error_t sh_process_line(char **i_line, t_sh_env **env)
{
  char *p_str;
  int proc_error;

  // generate and display prompt
  p_str = sh_get_prompt(*env);
  *i_line = readline(p_str);
  free (p_str);
  // validate input
  if (*i_line && sh_is_empty(*i_line))
  {
    free(*i_line);
    return (ERR_FAIL_GENERAL);
  }
  // tmp ignore signals during processing
  sh_configure_signal_state(HANDLER_IGN);
  // preocess quote-related aspects of input
  proc_error = sh_handle_quote_input(i_line, env, 0);
  //restore normal signal handling
  sh_configure_signal_state(HANDLER_INTERRUPT);
  // handle specific error scenarios
  if (proc_error == ERR_ERROR)
  {
    sh_destroy_env_list(*env);
    sh_execute_exit(NULL);
  }
  else if (proc_error == ERR_FAIL_GENERAL || !*i_line)
  {
    g_shell_exit_status = 130;
    return (ERR_DQUOTE_ABORTED);
  }
  return (ERR_NONE);
}

 /**
 * @brief Converts input line into tokens for parsing
 * 
 * Core responsibilities:
 * 1. Tokenize input line
 * 2. Validate token syntax
 * 3. Process tokens (format, remove braces)
 * 
 * @return Error status of tokenization
 */
error_t sh_tokenize_input (t_sh_token **tokens, char *input_line, t_sh_env **environment)
{
  error_t syntax_status;
  char *error_token;
  // initial syntax check(quote and structure)
  syntax_status = (!!sh_detect_quotes(input_line, NULL, QUOTE_NONE) << 1);
  // create tokens from input
  *tokens = sh_tokenize_input(input_line, QUOTE_NONE);
  // verify token structure
  syntax_status |= sh_validate_tokens(*tokens, &error_token);
  // handle syntax errors
  if (syntax_status & 0b11)
  {
    if (syntax_status & 0b10)
      sh_display_error(ERR_BAD_QUOTE, ": unexpected end of file");
    else
      sh_display_error(ERR_SYNTAX, error_token);
    sh_cleanup_token_list(*tokens);
    free(input_line);
    g_shell_exit_status = 2;
    return (ERR_FAIL_GENERAL);
  }
  // process tokens(expand home, remove braces)
  sh_expand_tilde(tokens, sh_find_env(*environment, "HOME"));
  sh_rmv_inv_parentheses(tokens);
  // additional validation
  if (!*tokens)
    return (ERR_FAIL_GENERAL);
  free(input_line);
  if (syntax_status & 0b100)
    sh_handle_heredoc_limit(*tokens, environment);
  return (ERR_NONE);
}

/**
 * @brief Executes the parsed command tree
 * 
 * Core responsibilities:
 * 1. Build execution tree
 * 2. Manage heredoc processing
 * 3. Execute commands
 * 4. Handle process waiting and exit status
 * 
 * @return Error status of execution
 */
error_t sh_execute_command_tree(t_sh_token **tokens, t_sh_node **execution_tree, t_sh_env **environment)
{
  t_sh_exec *executor;
  t_sh_pid *waiting_process;
  int process_exit_code;
  static int base_fd[2] = {0, 1};
  // build execution tree from tokens
  *execution_tree = sh_build_execution_tree(*tokens, environment);
  // cleanup tokens
  sh_cleanup_token_list(*tokens);
  sh_set_current_tree(*execution_tree);
  // process heredoc
  if (sh_process_herecod(*execution_tree))
    return (ERR_HEREDOC_ABORTED);
  // initialize executors
  executor = sh_exec_init();
  // tmp ignore signals during execution
  sh_configure_signal_state(HANDLER_IGN);
  // execute command multiplexer
  sh_execute_command_multiplex(*execution_tree, base_fd, executor, EXEC_WAIT);
  // wait for and process child processes
  while (executor->pids)
  {
    waiting_process = sh_pid_pop(&(executor->pids));
    waitpid(waiting_process->pid, &process_exit_code, 0);
    g_shell_exit_status = WEXITSTATUS(process_exit_code);
    sh_process_command_exit(process_exit_code);
    free(waiting_process);
  }
  // restor signal handling
  sh_configure_signal_state(HANDLER_INTERRUPT);
  free(executor);
  return (ERR_NONE);
}
/**
 * @brief Manages heredoc processing for execution tree
 * 
 * Core responsibilities:
 * 1. Process heredoc in command tree
 * 2. Handle potential errors
 * 
 * @return Error status of heredoc processing
 */

error_t   sh_process_heredoc(t_sh_node *execution_tree)
{
  int heredoc_completed;

  heredoc_completed = 0;
  if(sh_traverse_heredocs(execution_tree, &heredoc_completed) == ERR_HEREDOC_ABORTED)
  {
    sh_tree_fd_cleanup(execution_tree);
    sh_destroy_tree(execution_tree);
    return(ERR_FAIL_GENERAL);
  }
  return (ERR_NONE);
}

/**
 * @brief Main prompt handling function
 * 
 * Orchestrates the entire input-to-execution process
 */

void sh_handle_prompt(t_sh_env **environment)
{
  char *input_line;
  t_sh_token *tokens;
  t_sh_node *execution_tree;

  input_line = NULL;
  tokens = NULL;
  execution_tree = NULL;
  // process prompt line
  if (sh_process_line(&input_line, environment))
    return;
  // tokenize input
  if (sh_tokenize_input(&tokens, input_line, environment) || !tokens)
    return;
  // execute command tree
  if (sh_execute_command_tree(&tokens, &execution_tree, environment))
    return;
  // cleanup
  sh_tree_fd_cleanup(execution_tree);
  sh_destroy_tree(execution_tree);
}
