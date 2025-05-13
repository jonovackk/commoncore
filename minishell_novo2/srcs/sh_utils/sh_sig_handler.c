/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_sig_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:50 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:08:51 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Global variable to track shell's exit status
extern int g_shell_exit_status;

/**
 * @brief Ignore signal handler
 * 
 * Does nothing when a signal is received
 * Useful for temporarily blocking signal actions
 */
void sh_signal_ignore(int signal)
{
  (void)signal;
}

/**
 * @brief Interactive mode signal handler
 * 
 * Handles Ctrl+C in main shell prompt
 * - Sets exit status
 * - Prints new line
 * - Resets readline line
 * - Redraws prompt
 */
void sh_signal_interactive(int signal)
{
  if (signal == SIGINT)
  {
    g_shell_exit_status = 130;
    printf("^C\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
  }
}

/**
 * @brief Signal handler for quote input mode
 * 
 * Handles Ctrl+C during quote completion
 * - Prints new line
 * - Cleans up temporary resources
 * - Closes file descriptors
 * - Exits with status 130
 */

void sh_signal_quote_mode(int signal)
{
  int fd;
  // position cursor
  printf("\001\033[%dC\002", (int) ft_strlen(rl_prompt) + rl_point - 15);
  if (signal == SIGINT)
  {
    printf("^C\n");
    // free quote related tmp data
    free (sh_double_quote_state(NULL, 0));
    fd = *(int *)sh_double_quote_state(NULL, 1);
    sh_close_multiple_fd(4, fd,
      STDIN_FILENO,
        STDOUT_FILENO,
          STDERR_FILENO);
    g_shell_exit_status = 130;
    exit(130);
  }
}

/**
 * @brief Signal handler for heredoc mode
 * 
 * Handles Ctrl+C during heredoc input
 * - Prints new line
 * - Removes temporary heredoc file
 * - Cleans up environment
 * - Closes file descriptors
 * - Exits with status 130
 */

void sh_signal_heredoc_mode (int signal)
{
  int fd;

    // Position cursor
    printf("\001\033[%dC\002", (int) ft_strlen(rl_prompt) + rl_point - 15);
    if (signal == SIGINT)
    {
      printf("^C\n");
      // rmv tmp herecod file
      unlink(sh_heredoc_state(NULL, 0));
      // cleanup environment
      sh_destroy_env_list(sh_env_context(NULL));
      // free heredoc related resources
      free(sh_heredoc_state(NULL, 0));
      free(sh_heredoc_state(NULL, 1));
      // close fd
      fd = *(int *)sh_heredoc_state(NULL, 2);
      sh_close_multiple_fd(4, fd,
        STDIN_FILENO,
          STDOUT_FILENO,
            STDERR_FILENO);
      g_shell_exit_status = 130;
      exit(130);
   } 
}

/**
 * @brief Configures signal handling state
 * 
 * Manages terminal settings and signal handlers
 * Supports different signal handling modes
 * 
 * @param mode Signal handling mode 
 * (0: default, 1: custom handling)
 */

void sh_configure_signal_state(int mode)
{
  static struct termios terminal_settings;
  //array of signal handlers for diffrent modes
  static void (*signal_handlers[4])(int) = {
    sh_signal_ignore, sh_signal_interactive, sh_signal_quote_mode, 
      sh_signal_heredoc_mode
  };
  // capture current terminal settings
  tcgetattr(STDIN_FILENO, &terminal_settings);
  // modify terminal settings based on mode
  if (!mode)
    terminal_settings.c_lflag |= ECHOCTL;
  else
    terminal_settings.c_lflag &= ~ECHOCTL;
  //apply terminal setting verify if TCSANOW if defined and allowed
  tcsetattr(STDIN_FILENO, TCSANOW, &terminal_settings);
  // set signal handlers for SIGINT and SIGQUIT
  signal(SIGINT, signal_handlers[mode]);
  signal(SIGQUIT, signal_handlers[mode]);
}