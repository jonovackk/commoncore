#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H



/* sh_cd_h.c */

void    sh_dir_vars(t_sh_env *envp, t_sh_env **dir_vars);

error_t sh_change_directory(const char *target);

error_t sh_cd_target(int argc, char **argv, t_sh_env **vars, int out);

int sh_execute_cd(t_sh_cmd *cmd);

/* sh_echo_h.c*/

int sh_n_option(char *str);

int sh_echo_execute(t_sh_cmd *command);

/* sh_env_h.c */

int sh_env_list_size(t_sh_env *env);

char *sh_format_env_var(t_sh_env *env, int format, int include_name);

char **sh_create_env_array(t_sh_env *env, int format);

int sh_execute_env(t_sh_cmd *cmd);


/* sh_exit_h.c */

long sh_exit_status_atoi(char *str);

void sh_handle_exit(int exit_code, error_t ec, t_sh_cmd *cmd);

int sh_exit_builtin(t_sh_cmd *cmd);

/* sh_export_h.c */

int     sh_export_syntax(char *str);

int     sh_display_expor_var(t_sh_cmd *cmd);

int     sh_update_env_var(t_sh_cmd *cmd, char *tmp);

int     sh_export_builtin(t_sh_cmd *cmd);

/* sh_pwd_h.c */

char    *sh_trim_pwd(char *str);

char    *sh_get_cwd(void);

int     sh_execute_pwd(t_sh_cmd *cmd);

char    *sh_get_prompt(t_sh_env *envp);

/* sh_unset_h.c */

int sh_unset_variables(t_sh_cmd *cmd);



#endif