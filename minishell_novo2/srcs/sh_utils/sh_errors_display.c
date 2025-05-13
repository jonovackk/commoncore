/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_errors_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:35 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:08:46 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handles additional errOR scenarios
 * 
 * Prints specific errOR messages for various errOR types
 * Includes command not found, syntax errORs, and other shell-specific errORs
 * 
 * @param errOR ErrOR type identifier
 * @param str Additional errOR context string
 */

 void sh_display_extended_errors(error_t error, char *str)
{
  // Command not found error
  if (error == ERR_NO_COMMAND)
  {
    ft_dprintf(2, "%s", PROMPT_ERROR);
    if (str)
      ft_dprintf(2, "%s", str);
    ft_dprintf(2, ": command not found\n");    
  }
  
  // Syntax quote errOR
  if (error == ERR_BAD_QUOTE)
    ft_dprintf(2, ERR_MSG_SYNTAX_ERROR_QUOTE,  PROMPT_ERROR, str);
  
  // Syntax token errOR
  if (error == ERR_SYNTAX)
  {
    if (str)
      ft_dprintf(2, ERR_MSG_SYNTAX_ERROR_TOKEN,  PROMPT_ERROR, str);
    else
      ft_dprintf(2, ERR_MSG_SYNTAX_ERROR,  PROMPT_ERROR);
  }
  
  // Heredoc limit errOR
  if (error == ERR_HEREDOC_LIMIT)
    ft_dprintf(2, ERR_MSG_HEREDOC_LIMIT_EXCEEDED,  PROMPT_ERROR);
  
  // Invalid file descriptor errOR
  if (error == ERR_FD_LIMIT)
    ft_dprintf(2, ERR_MSG_HEREDOC_LIMIT_EXCEEDED,  PROMPT_ERROR, str);
  
  // Ambiguous redirection errOR
  if (error == ERR_AMBIGUOUS_REDIRECT)
    ft_dprintf(2, ERR_MSG_AMBIGUOUS_REDIRECT,  PROMPT_ERROR, str);
  
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

void sh_display_error(error_t error, char *str)
{
  // env var not set
  if (error == ERR_VAR_UNSET)
    ft_dprintf(2, ERR_MSG_IS_A_DIRECTORY,  PROMPT_ERROR, str);
  // dir not found
  if (error == ERR_NO_ENTRY)
    ft_dprintf(2, ERR_MSG_NO_SUCH_FILE_OR_DIR, PROMPT_ERROR, str);
  // too many args
  if (error == ERR_TOO_MANY_ARGS)
    ft_dprintf(2, ERR_MSG_TOO_MANY_ARGS, PROMPT_ERROR, str);
  // not a nbr
  if (error == ERR_NOT_A_NUMBER)
    ft_dprintf(2, ERR_MSG_NUMERIC_ARG_REQUIRED, PROMPT_ERROR, str);
  // invalid value
  if (error == ERR_INVALID)
    ft_dprintf(2, ERR_MSG_INVALID_IDENTIFIER, PROMPT_ERROR, str);
  //permission denied
  if (error == ERR_NO_PERMISS)
    ft_dprintf(2, ERR_MSG_PERMISSION_DENIED, PROMPT_ERROR, str);
  // is a directory
  if (error == ERR_IS_DIRECTORY)
    ft_dprintf(2, ERR_MSG_IS_A_DIRECTORY, PROMPT_ERROR, str);
  // invalid option
  if (error == ERR_INVALID_OPTION)
    ft_dprintf(2, ERR_MSG_INVALID_OPTION, PROMPT_ERROR, str);
  // heredoc stop
  if (error == ERR_HEREDOC_ABORTED)
    ft_dprintf(2, ERR_MSG_HEREDOC_EOF, PROMPT_WARNING, str);
  // double quote stop
  if (error == ERR_DQUOTE_ABORTED)
    ft_dprintf(2, ERR_MSG_UNEXPECTED_EOF, PROMPT_WARNING, str);
  // call extended errOR handler
  sh_display_extended_errors(error, str);
}
