/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quote_pt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:21 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:08:22 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// defined g_shell_exit_status in global.c
extern int g_shell_exit_status;
/**
 * @brief Opens a new line for quote input
 * 
 * Handles different quote states and writes input to a file
 * 
 * @param tmp_fd File descriptor for temporary file
 * @param quote_state Current quote state (single or double)
 * @return Inputted line
 */
char *sh_opendquote(int tmp_fd, t_quote_state quote_state)
{
  char *line;
  // select prompt based on quote type
  if (quote_state == QUOTE_SINGLE)
    line = readline("quote> ");
  if (quote_state == QUOTE_DOUBLE)
    line = readline("dquote> ");
  // write nl and input to tmp file
  write (tmp_fd, "\n", 1);
  write (tmp_fd, line, ft_strlen(line));
  return(line);
}

/**
 * @brief Retrieves the complete quote input line
 * 
 * Reads from a temporary file, joins multiple lines if needed
 * 
 * @param line Initial input line
 * @param tmp_file Temporary file path
 * @param status Process status
 * @return Consolidated input line
 */

 char *sh_get_dquote_line(char *line, char *tmp_file, int status)
 {
  char *result;
  int tmp_fd;
  // open tmp file for reading
  tmp_fd = open(tmp_file, O_RDONLY);
  result = NULL;
  // set global exit status from process status
  g_shell_exit_status = WEXITSTATUS(status);
  // read and consolidate line from tmp file
  line = get_next_line(tmp_fd);
  while (line)
  {
    result = ft_strjoin(result, line, NULL, 0b11);
    line = get_next_line(tmp_fd);
  }
  // clean up tmp files
  close (tmp_fd);
  unlink(tmp_file);
  return(result);
 }

 /**
 * @brief Handles quote input in a child process
 * 
 * Forks a child process to manage quote input separately
 * 
 * @param line Input line
 * @param env Environment variables
 * @param tmp Temporary file path
 * @return File descriptor or error code
 */

 int sh_get_dquote(char *line, t_sh_env **env, char *tmp)
 {
  int tmp_fd;
  pid_t quote_pid;
  // fork child process for quote handling
  quote_pid = fork();
  if (quote_pid == -1)
    return (-1);
  // child process
  if (quote_pid == 0)
  {
    // prepare for signal handling
    rl_catch_signals = 1;
    sh_configure_signal_state(HANDLER_DQUOTE);
    // create tmp file
    tmp_fd = open (tmp, O_CREAT | O_EXCL | O_WRONLY, 0600);
    // store fd for later use
    sh_double_quote_state((char *)&tmp_fd, 1);
    // clean up resources
    rl_clear_history();
    sh_destroy_env_list(*env);
    free(tmp);
    // write original line to tmp file
    write (tmp_fd, line, ft_strlen(line));
    // processe quote-related operations
    sh_handle_unclosed_quotes(&line, tmp_fd, QUOTE_NONE);
    free(line);
    //close all fd's
    sh_close_multiple_fd(4, tmp_fd,
      STDIN_FILENO,
      STDOUT_FILENO,
      STDERR_FILENO);
    exit(EXIT_SUCCESS);
  }
  // parent process
  free(line);
  waitpid(quote_pid, &tmp_fd, 0);
  return(tmp_fd);
 }

 /**
 * @brief Manages quote-related input processing
 * 
 * Handles quote completion, history, and error scenarios
 * 
 * @param line Input line to process
 * @param env Environment variables
 * @param status Current process status
 * @return Error status of quote handling
 */

 error_t sh_quote_handler(char **line, t_sh_env **env, int status)
 {
  char *dquote_file;
  char *history_line;
  char *quote_str;
  // validate input line
  if (!*line)
    return (ERR_ERRORS);
  history_line = *line;
  // create tmp file for quote processing
  dquote_file = generate_temp_filename(".dquote", 16);
  // check if quote processing is needed
  if (sh_detect_quotes(*line, NULL, QUOTE_NONE))
  {
    // process quote input
    status = sh_get_dquote(*line, env, dquote_file);
    history_line = sh_get_dquote_line(*line, dquote_file, status);
  }
  // add processed line to history
  add_history(history_line);
  free(dquote_file);
  *line = history_line;
  // handle interrupt status
  if (WEXITSTATUS(status) == 130)
  {
    free (*line);
    return (ERR_FAIL_GENERAL);
  }
  // final quote error check
  quote_str = ft_strdup(" ");
  if (sh_detect_quotes(*line, quote_str, QUOTE_NONE))
    sh_display_error(ERR_DQUOTE_ABORTED, quote_str);
  free(quote_str);
  return (ERR_NONE);
 }
