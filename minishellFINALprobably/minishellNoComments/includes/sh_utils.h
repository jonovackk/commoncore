/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:06:24 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 15:06:24 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SH_UTILS_H
# define SH_UTILS_H

# include "sh_enumerates.h"
# include "sh_managers.h"

/* sh_env_setup.c */
t_sh_env		*sh_env_context(t_sh_env **env);
void			sh_env_defaults(t_sh_env **env, char **argv);
t_sh_env		*sh_env_init(char **argv, char **envp);

/* sh_errors_display.c */
/* Changed static function to non-static since it's used externally */
void			sh_display_extended_errors(error_t err, char *str);
void			sh_display_error(error_t err, char *str);

/* sh_sig_handler.c */
void			sh_signal_heredoc_mode(int signal);
void			sh_configure_signal_state(int mode);

/* minishell.c */
int				is_non_empty(const char *str);
char			*generate_temp_filename(const char *prefix, int length);
int				main(int argc, char **argv, char **envp);

t_quote_state	detect_quote_type(const char *str);

#endif