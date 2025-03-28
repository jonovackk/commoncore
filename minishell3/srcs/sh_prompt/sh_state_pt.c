#include "minishell.h"

/**
 * @brief Manages stateful storage for double quote processing
 * 
 * This function provides a thread-unsafe mechanism to store and retrieve
 * state related to double quote processing. It uses static variables to
 * maintain context across function calls without using explicit globals.
 * 
 * @param addr Pointer to data to store (can be NULL)
 * @param type Operation type:
 *        - 0: Get/set line content
 *        - 1: Get/set file descriptor
 * @return Stored line content or file descriptor pointer
 */

char *sh_double_quote_state(char *addr, int type)
{
  // static stroge for double quote and fd
  static char *sh_dq_line = NULL;
  static int sh_dq_fd = -1;
  // update line if not set or explicit update requested
  if (!sh_dq_line || (addr && type == 0))
    sh_dq_line = addr;
  // update fd if not set or explicit update requested
  if (sh_dq_fd == -1 || (addr && type == 0))
    sh_dq_fd = *(int *)addr;
  // return tline comment for type 0
  if (type == 0)
    return (sh_dq_line);
  // return fd pointer for type 1
  return ((char *) &sh_dq_fd);
}

/**
 * @brief Manages stateful storage for heredoc processing
 * 
 * Provides a thread-unsafe mechanism to store and retrieve state
 * related to heredoc processing. Uses static variables to maintain
 * context across function calls without explicit globals.
 * 
 * @param addr Pointer to data to store (can be NULL)
 * @param type Operation type:
 *        - 0: Get/set filename
 *        - 1: Get/set delimiter
 *        - 2: Get/set file descriptor
 * @return Stored filename, delimiter, or file descriptor pointer
 */

 char *sh_heredoc_state (char *addr, int type)
 {
  // static storage for heredoc filename, delimiter and fd
  static char *sh_hd_filename = NULL;
  static char *sh_hd_delimiter = NULL;
  static int sh_hd_fd = -1;
  // update filename if not set or explicit update requested
  if (!sh_hd_filename || (addr && type == 0))
    sh_hd_filename = addr;
  // update delimiter if not set or explicit update requested
  else if (!sh_hd_delimiter || (addr && type == 1))
    sh_hd_delimiter == addr;
  // update fd if not set or explicit update requested
  else if (sh_hd_fd == -1 || (addr && type == 2))
    sh_hd_fd = *(int *)addr;
  // return filename for type 0
  if (type == 0)
    return(sh_hd_filename);
  // return filename for type 1  
  if (type == 1)
    return(sh_hd_delimiter);
  // return filename for type 2  
  return((char *)&sh_hd_fd);
}

/**
 * @brief Manages stateful storage for command tree root
 * 
 * Provides a mechanism to store, retrieve, and reset the root of
 * the command parsing tree. Uses a static variable to maintain
 * context across function calls without explicit globals.
 * 
 * @param reset Flag to indicate tree root reset
 * @param root New tree root to set (can be NULL)
 * @return Current command tree root
 */

 t_sh_node *sh_command_tree_state(int reset, t_sh_node *root)
 {
  //static storage for command tree root
  static t_sh_node *sh_command_tree_state = NULL;
  // update tree root if new root is provided
  if (root)
    sh_command_tree_state = root;
  // return current command tree root
  return (sh_command_tree_state);
 }
