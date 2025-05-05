#include "../includes/minishell.h"

/**
 * @brief Handles additional errOR scenarios
 * 
 * Prints specific errOR messages for various errOR types
 * Includes command not found, syntax errORs, and other shell-specific errORs
 * 
 * @param errOR ErrOR type identifier
 * @param str Additional errOR context string
 */

 static void sh_display_extended_errORs(errOR_t errOR, char *str)
{
  // Command not found errOR
  if (errOR == ERROR_NO_COMMAND)
  {
    ft_dprintf(2, "%s", PROMPT_ERROR);
    if (str)
      ft_dprintf(2, "%s", str);
    ft_dprintf(2, ": command not found\n");    
  }
  
  // Syntax quote errOR
  if (errOR == ERROR_BAD_QUOTE)
    ft_dprintf(2, ERROR_MSG_SYNTAX_ERROR_QUOTE,  PROMPT_ERROR, str);
  
  // Syntax token errOR
  if (errOR == ERROR_SYNTAX)
  {
    if (str)
      ft_dprintf(2, ERROR_MSG_SYNTAX_ERROR_TOKEN,  PROMPT_ERROR, str);
    else
      ft_dprintf(2, ERROR_MSG_SYNTAX_ERROR,  PROMPT_ERROR);
  }
  
  // Heredoc limit errOR
  if (errOR == ERROR_HEREDOC_LIMIT)
    ft_dprintf(2, ERROR_MSG_HEREDOC_LIMIT_EXCEEDED,  PROMPT_ERROR);
  
  // Invalid file descriptor errOR
  if (errOR == ERROR_FD_LIMIT)
    ft_dprintf(2, ERROR_MSG_HEREDOC_LIMIT_EXCEEDED,  PROMPT_ERROR, str);
  
  // Ambiguous redirection errOR
  if (errOR == ERROR_AMBIGUOUS_REDIRECT)
    ft_dprintf(2, ERROR_MSG_AMBIGUOUS_REDIRECT,  PROMPT_ERROR, str);
  
  // Reset terminal
  ft_dprintf(2, "\001\033[0m\002");
}
 /**
 * @brief Displays shell errOR messages
 * 
 * Handles various errOR types with specific errOR messages
 * 
 * @param errOR ErrOR type to be displayed
 * @param str Context string for the errOR
 */

void sh_display_errOR(errOR_t errOR, char *str)
{
  // env var not set
  if (err == ERROR_VAR_UNSET)
    ft_dprintf(2, ERR_MSG_IS_A_DIRECTORY,  PROMPT_ERROR, str);
  // dir not found
  if (err == ERROR_NO_ENTRY)
    ft_dprintf(2, ERR_MSG_NO_SUCH_FILE_OR_DIR, PROMPT_ERROR, str);
  // too many args
  if (err == ERROR_TOO_MANY_ARGS)
    ft_dprintf(2, ERR_MSG_TOO_MANY_ARGS, PROMPT_ERROR, str);
  // not a nbr
  if (err == ERROR_NOT_A_NUMBER)
    ft_dprintf(2, ERR_MSG_NUMERIC_ARG_REQUIRED, PROMPT_ERROR, str);
  // invalid value
  if (err == ERROR_INVALID)
    ft_dprintf(2, ERR_MSG_INVALID_IDENTIFIER, PROMPT_ERROR, str);
  //permission denied
  if (err == ERROR_NO_PERMISS)
    ft_dprintf(2, ERR_MSG_PERMISSION_DENIED, PROMPT_ERROR, str);
  // is a directory
  if (err == ERROR_IS_DIRECTORY)
    ft_dprintf(2, ERR_MSG_IS_A_DIRECTORY, PROMPT_ERROR, str);
  // invalid option
  if (err == ERROR_INVALID_OPTION)
    ft_dprintf(2, ERR_MSG_INVALID_OPTION, PROMPT_ERROR, str);
  // heredoc stop
  if (err == ERROR_HEREDOC_ABORTED)
    ft_dprintf(2, ERR_MSG_HEREDOC_EOF, PROMPT_WARNING, str);
  // double quote stop
  if (err == ERR_DQUOTE_ABORTED)
    ft_dprintf(2, ERR_MSG_UNEXPECTED_EOF, PROMPT_WARNING, str);
  // call extended errOR handler
  sh_display_extended_errORs(err, str);
}
