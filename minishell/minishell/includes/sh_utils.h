





// sh_env_setup.c


t_sh_env *sh_env_context(t_sh_env **env);

void sh_env_defaults(t_sh_env **env, char **argv);

t_sh_env *sh_env_init(char **argv, char **envp);


// sh_errors_display.c


static void sh_display_extended_errors(t_error err, char *str);

void sh_display_error(t_error err, char *str);


// sh_sig_handler.c

void sh_signal_heredoc_mode (int signal);

void sh_configure_signal_state(int mode);
