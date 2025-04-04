#include "../../includes/minishell.h"

/**
 * @brief Handles heredoc limit error
 * 
 * Displays error message, cleans up resources, and exits
 * 
 * @param tokens Token list to be cleared
 * @param environment Environment to be cleared
 */
void sh_handle_heredoc_limit(t_sh_token *tokens, t_sh_env **environment)
{
  // display heredoc limit error
  sh_display_error(ERR_HEREDOC_LIMIT, NULL);
  // cleanup resources
  sh_cleanup_token_list(tokens);
  sh_destroy_env_list(*environment);
  //exit whit error status
  exit(ERR_FAIL_UNKNOWN);
}

/**
 * @brief Parses and processes a single line of heredoc input
 * 
 * Handles variable expansion and writes line to file
 * 
 * @param line Pointer to input line
 * @param fd Heredoc file descriptor
 * @param expand Flag for variable expansion
 */
void sh_parse_heredoc_line(char **line, int fd, int expand)
{
  static int first_line;

  first_line = 0;
  // expand vars if needed
  if (expand)
  sh_replace_env_vars(sh_env_context(), line, QUOTE_IGNORE);
  // write line to file
  write (fd, *line, ft_strlen(*line));
  // add nl for subsequent lines
  if (first_line++)
    write(fd, "\n", 1);
  // free current line and read next
  free(*line);
  *line = readline(RD_HEREDOC); 
}


/**
 * @brief Processes heredoc input for a single delimiter
 * 
 * Reads input lines until delimiter is found
 * 
 * @param delimiter Heredoc termination string
 * @param temp_file Temporary file path
 * @param fd File descriptor for writing
 * @return Error status
 */
int sh_process_heredoc_line(char *delimiter, char *temp_file, int fd)
{
  char *line;
  int should_expand;
  //validate fd
  if (fd == -1)
  {
    free(delimiter);
    return(ERR_FAIL_GENERAL);
  }
  line = NULL;
  // determine if var expansion is needed
  should_expand = !(ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''));
  // remove quotes from frlimiter
  sh_rmv_quotes(&delimiter, QUOTE_NONE);
  // store tmp file and delimiter for signal handling
  sh_set_heredoc_holder(temp_file, 0);
  sh_set_heredoc_holder(delimiter, 1);
  sh_set_heredoc_holder((char*)&fd, 2);
  // read and process initial line
  sh_parse_heredoc_line(&line, fd, should_expand);
  // continue reading until delimiter or file acess fails
  while (line && 
           ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) &&
           !access(temp_file, F_OK))
    {
        sh_parse_heredoc_line(&line, fd, should_expand);
    }
  // cleanup resources
  free(delimiter);
  free(temp_file);
  //handle empty input
  if (!line)
    return(ERR_FAIL_GENERAL);
  free(line);
  return(ERR_NONE);
}
/**
 * @brief Handles heredoc process exit scenarios
 * 
 * Processes different exit codes and manages resources
 * 
 * @param delimiter Heredoc termination string
 * @param temp_file Temporary file path
 * @param exit_status Process exit status
 * @return File descriptor or error code
 */
int sh_handle_heredoc_exit(char *delimiter, char *temp_file, int exit_status)
{
  int fd;
  //extract exit status
  exit_status = WEXITSTATUS(exit_status);
  // handle diffrent exit scenatios
  if (exit_status == 1)
  {
    // rmv quote from delimiter
    sh_rmv_quotes(&delimiter, QUOTE_NONE);
    //display heredoc stop error
    sh_display_error(ERR_HEREDOC_ABORTED, delimiter);
  }
  else if (exit_status == 130)
  {
    unlink(temp_file);
    free(delimiter);
    free(temp_file);
    // set global exit value
    g_shell_exit_status = 130;
    return(FILE_HEREDOC_TEMP);
  }
  // open and return fd
  fd = open(temp_file, O_RDONLY);
  unlink(temp_file);
  free(delimiter);
  free(temp_file);
  return(fd);
}

/**
 * @brief Creates a heredoc process
 * 
 * Forks a child process to handle heredoc input
 * 
 * @param delimiter Heredoc termination string
 * @param temp_file Temporary file path
 * @return File descriptor or error code
 */
int sh_create_heredoc(char *delimiter, char *temp_file)
{
    pid_t heredoc_pid;
    int fd;
    int error_code;
    // temporarily ignore signals
    sh_configure_signal_state(HANDLER_IGN);
    // fork heredoc process
    heredoc_pid = fork();
    if (heredoc_pid == -1)
        return (-1);
    // child process
    if (heredoc_pid == 0)
    {
        // prepare for signal handling
        rl_catch_signals = 1;
        sh_configure_signal_state(HANDLER_HEREDOC);
        // create temporary file
        fd = open(temp_file, O_CREAT | O_EXCL | O_WRONLY, 0600);
        // cleanup resources
        sh_destroy_tree(sh_get_current_tree());
        rl_clear_history();
        // process heredoc
        error_code = sh_process_heredoc_line(delimiter, temp_file, fd);
        // final cleanup
        sh_destroy_env_list(sh_env_context(NULL));
        sh_close_multiple_fd(4, fd, 
                              STDIN_FILENO, 
                              STDOUT_FILENO, 
                              STDERR_FILENO);
        // exit with error code
        exit(error_code);
    }
    // parent process
    waitpid(heredoc_pid, &error_code, 0);
    sh_configure_signal_state(HANDLER_INTERRUPT);
    // handle and return heredoc result
    return sh_handle_heredoc_exit(delimiter, temp_file, error_code);
}
