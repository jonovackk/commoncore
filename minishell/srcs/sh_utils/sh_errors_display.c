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

 static void sh_display_extended_errors(error_t err, char *str)
{
  // Command not found error
  if (err == ERR_NO_COMMAND)
  {
    ft_dprintf(2, "%s", PROMPT_ERROR);
    if (str)
      ft_dprintf(2, "%s", str);
    ft_dprintf(2, ": command not found\n");    
  }
  
  // Syntax quote error
  if (err == ERR_BAD_QUOTE)
    ft_dprintf(2, ERR_MSG_SYNTAX_ERROR_QUOTE,  PROMPT_ERROR, str);
  
  // Syntax token error
  if (err == ERR_SYNTAX)
  {
    if (str)
      ft_dprintf(2, ERR_MSG_SYNTAX_ERROR_TOKEN,  PROMPT_ERROR, str);
    else
      ft_dprintf(2, ERR_MSG_SYNTAX_ERROR,  PROMPT_ERROR);
  }
  
  // Heredoc limit error
  if (err == ERR_HEREDOC_LIMIT)
    ft_dprintf(2, ERR_MSG_HEREDOC_LIMIT_EXCEEDED,  PROMPT_ERROR);
  
  // Invalid file descriptor error
  if (err == ERR_FD_LIMIT)
    ft_dprintf(2, ERR_MSG_HEREDOC_LIMIT_EXCEEDED,  PROMPT_ERROR, str);
  
  // Ambiguous redirection error
  if (err == ERR_AMBIGUOUS_REDIRECT)
    ft_dprintf(2, ERR_MSG_AMBIGUOUS_REDIRECT,  PROMPT_ERROR, str);
  
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

void sh_display_error(error_t err, char *str)
{
  // env var not set
  if (err == ERR_VAR_UNSET)
    ft_dprintf(2, ERR_MSG_VAR_NOT_SET,  PROMPT_ERROR, str);
  // dir not found
  if (err == ERR_NO_ENTRY)
    ft_dprintf(2, ERR_MSG_NO_SUCH_FILE_OR_DIR, PROMPT_ERROR, str);
  // too many args
  if (err == ERR_TOO_MANY_ARGS)
    ft_dprintf(2, ERR_MSG_TOO_MANY_ARGS, PROMPT_ERROR, str);
  // not a nbr
  if (err == ERR_NOT_A_NUMBER)
    ft_dprintf(2, ERR_MSG_NUMERIC_ARG_REQUIRED, PROMPT_ERROR, str);
  // invalid value
  if (err == ERR_INVALID)
    ft_dprintf(2, ERR_MSG_INVALID_IDENTIFIER, PROMPT_ERROR, str);
  //permission denied
  if (err == ERR_NO_PERMISS)
    ft_dprintf(2, ERR_MSG_PERMISSION_DENIED, PROMPT_ERROR, str);
  // is a directory
  if (err == ERR_IS_DIRECTORY)
    ft_dprintf(2, ERR_MSG_IS_A_DIRECTORY, PROMPT_ERROR, str);
  // invalid option
  if (err == ERR_INVALID_OPTION)
    ft_dprintf(2, ERR_MSG_INVALID_OPTION, PROMPT_ERROR, str);
  // heredoc stop
  if (err == ERR_HEREDOC_ABORTED)
    ft_dprintf(2, ERR_MSG_HEREDOC_EOF, PROMPT_WARNING, str);
  // double quote stop
  if (err == ERR_DQUOTE_ABORTED)
    ft_dprintf(2, ERR_MSG_UNEXPECTED_EOF, PROMPT_WARNING, str);
  // call extended error handler
  sh_display_extended_errors(err, str);
}