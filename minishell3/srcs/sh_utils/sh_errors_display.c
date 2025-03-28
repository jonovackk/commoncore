#include "minishell.h"

/**
 * @brief Handles additional error scenarios
 * 
 * Prints specific error messages for various error types
 * Includes command not found, syntax errors, and other shell-specific errors
 * 
 * @param err Error type identifier
 * @param str Additional error context string
 */

 static void sh_display_extended_errors(t_error err, char *str)
{
  // Command not found error
  if (err == ERROR_COMMAND_NOT_FOUND)
  {
    ft_dprintf(2, "%s", SHELL_ERROR_PREFIX);
    if (str)
      ft_dprintf(2, "%s", str);
    ft_dprintf(2, ": command not found\n");    
  }
  
  // Syntax quote error
  if (err == ERROR_SYNTAX_QUOTE)
    ft_dprintf(2, ERROR_SYNTAX_QUOTE_MSG, SHELL_ERROR_PREFIX, str);
  
  // Syntax token error
  if (err == ERROR_SYNTAX_TOKEN)
  {
    if (str)
      ft_dprintf(2, ERROR_SYNTAX_TOKEN_MSG, SHELL_ERROR_PREFIX, str);
    else
      ft_dprintf(2, ERROR_SYNTAX_TOKEN_GENERIC_MSG, SHELL_ERROR_PREFIX);
  }
  
  // Heredoc limit error
  if (err == ERROR_HEREDOC_LIMIT)
    ft_dprintf(2, ERROR_HEREDOC_LIMIT_MSG, SHELL_ERROR_PREFIX);
  
  // Invalid file descriptor error
  if (err == ERROR_INVALID_FD)
    ft_dprintf(2, ERROR_INVALID_FD_MSG, SHELL_ERROR_PREFIX, str);
  
  // Ambiguous redirection error
  if (err == ERROR_AMBIGUOUS_REDIRECT)
    ft_dprintf(2, ERROR_AMBIGUOUS_REDIRECT_MSG, SHELL_ERROR_PREFIX, str);
  
  // Reset terminal
  ft_dprintf(2, "\001\033[0m\002");
}
 /**
 * @brief Displays shell error messages
 * 
 * Handles various error types with specific error messages
 * 
 * @param err Error type to be displayed
 * @param str Context string for the error
 */

void sh_display_error(t_error err, char *str)
{
  // env var not set
  if (err == ERROR_ENV_VAR_NOT_SET)
    ft_dprintf(2, ERROR_ENV_VAR_NOT_SET_MSG, SHELL_ERROR_PREFIX, str);
  // dir not found
  if (err == ERROR_DIR_NOT_FOUND)
    ft_dprintf(2, ERROR_DIR_NOT_FOUND_MSG,SHELL_ERROR_PREFIX, str);
  // too many args
  if (err == ERROR_TOO_MANY_ARGS)
    ft_dprintf(2, ERROR_TOO_MANY_ARGS_MSG,SHELL_ERROR_PREFIX, str);
  // not a nbr
  if (err == ERROR_NOT_NUMERIC)
    ft_dprintf(2, ERROR_NOT_NUMERIC_MSG,SHELL_ERROR_PREFIX, str);
  // invalid value
  if (err == ERROR_INVALID_VALUE)
    ft_dprintf(2, ERROR_INVALID_VALUE_MSG,SHELL_ERROR_PREFIX, str);
  //permission denied
  if (err == ERROR_PERMISSION_DENIED)
    ft_dprintf(2, ERROR_PERMISSION_DENIED_MSG,SHELL_ERROR_PREFIX, str);
  // is a directory
  if (err == ERROR_IS_DIRECTORY)
    ft_dprintf(2, ERROR_IS_DIRECTORY_MSG,SHELL_ERROR_PREFIX, str);
  // invalid option
  if (err == ERROR_INVALID_OPTION)
    ft_dprintf(2, ERROR_INVALID_OPTION_MSG,SHELL_ERROR_PREFIX, str);
  // heredoc stop
  if (err == ERROR_HEREDOC_STOP)
    ft_dprintf(2, ERROR_HEREDOC_STOP_MSG,SHELL_ERROR_PREFIX, str);
  // double quote stop
  if (err == ERROR_DQUOTE_STOP)
    ft_dprintf(2, ERROR_DQUOTE_STOP_MSG,SHELL_ERROR_PREFIX, str);
  // call extended error handler
  sh_display_extended_errors(err, str);
}