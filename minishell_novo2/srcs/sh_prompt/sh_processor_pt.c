/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_processor_pt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:17 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:08:18 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

  // Input validation
  if (!i_line || !env || !*env)
    return (ERR_FAIL_GENERAL);
    
  // Initialize to NULL for safety
  *i_line = NULL;

  // Generate and display prompt
  p_str = sh_get_prompt(*env);
  if (!p_str)
    return (ERR_FAIL_GENERAL);
    
  // Read user input  
  *i_line = readline(p_str);
  free(p_str);
  p_str = NULL;
  
  // Check if readline returned NULL (EOF/Ctrl+D)
  if (!*i_line)
    return (ERR_FAIL_GENERAL);
    
  // Check if input is empty (only whitespace)
  if (!is_non_empty(*i_line))
  {
    free(*i_line);
    *i_line = NULL;
    return (ERR_FAIL_GENERAL);
  }
  
  // Add valid command to history
  add_history(*i_line);
  
  // Temporarily ignore signals during processing
  sh_configure_signal_state(HANDLER_IGN);
  
  // Process quote-related aspects of input
  proc_error = sh_quote_handler(i_line, env, 0);
  
  // Restore normal signal handling
  sh_configure_signal_state(HANDLER_INTERRUPT);
  
  // Handle specific error scenarios
  if (proc_error == ERR_ERRORS)
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
error_t sh_tokenize_input(t_sh_token **tokens, char *input_line, t_sh_env **environment)
{
  error_t syntax_status;
  char *error_token = NULL;
  
  // Input validation
  if (!tokens || !input_line || !environment || !*environment)
    return (ERR_FAIL_GENERAL);
    
  // Initialize tokens to NULL for safety
  *tokens = NULL;
    
  // Initial syntax check (quote and structure)
  syntax_status = (!!sh_detect_quotes(input_line, NULL, QUOTE_NONE) << 1);
  
  // Create tokens from input
  *tokens = sh_tokenizer_input(input_line, QUOTE_NONE);
  
  // Verify token structure
  syntax_status |= sh_validate_tokens(*tokens, &error_token);
  
  // Handle syntax errors
  if (syntax_status & 0b11)
  {
    if (syntax_status & 0b10)
      sh_display_error(ERR_BAD_QUOTE, ": unexpected end of file");
    else
      sh_display_error(ERR_SYNTAX, error_token);
      
    sh_rmv_inv_parentheses(tokens);
    free(input_line);
    input_line = NULL;
    g_shell_exit_status = 2;
    return (ERR_FAIL_GENERAL);
  }
  
  // Process tokens (expand home, remove braces)
  sh_expand_tilde(tokens, sh_find_env(*environment, "HOME"));
  sh_rmv_inv_parentheses(tokens);
  
  // Additional validation
  if (!*tokens)
  {
    free(input_line);
    input_line = NULL;
    return (ERR_FAIL_GENERAL);
  }
  
  free(input_line);
  input_line = NULL;
  
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
  
  // FIX: Check for NULL tokens
  if (!tokens || !*tokens)
    return (ERR_FAIL_GENERAL);
    
  // build execution tree from tokens
  *execution_tree = sh_build_tree(*tokens, environment);
  // cleanup tokens
  sh_free_token_list(*tokens);
  sh_command_tree_state(0, *execution_tree);
  
  // FIX: Check for NULL execution_tree
  if (!*execution_tree)
    return (ERR_FAIL_GENERAL);
    
  // process heredoc
  if (sh_process_heredoc(*execution_tree))
    return (ERR_HEREDOC_ABORTED);
  // initialize executors
  executor = sh_exec_init();
  
  // FIX: Check for NULL executor
  if (!executor)
  {
    sh_tree_fd_cleanup(*execution_tree);
    sh_destroy_tree(*execution_tree);
    return (ERR_FAIL_GENERAL);
  }
  
  // tmp ignore signals during execution
  sh_configure_signal_state(HANDLER_IGN);
  // execute command multiplexer
  sh_execute_command_multiplex(*execution_tree, base_fd, executor, EXEC_WAIT);
  // wait for and process child processes
  while (executor->running_procs)
  {
    waiting_process = sh_pid_pop(&(executor->running_procs));
    if (waiting_process) {  // FIX: Check for NULL
      waitpid(waiting_process->pid, &process_exit_code, 0);
      g_shell_exit_status = WEXITSTATUS(process_exit_code);
      sh_process_command_exit(process_exit_code);
      free(waiting_process);
    }
  }
  // restore signal handling
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

 error_t sh_process_heredoc(t_sh_node *execution_tree)
 {
   int heredoc_completed;
 
   // FIX: Check for NULL execution_tree
   if (!execution_tree)
     return (ERR_FAIL_GENERAL);
     
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
 
   // FIX: Check for NULL environment
   if (!environment || !*environment)
     return;
     
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

 
