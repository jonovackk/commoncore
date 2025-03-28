#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H


void    load_directory_env(t_sh_env *envp, t_sh_env **vars);

error_t     change_directory(const char *target);

error_t     process_cd_args(int argc, char **argv, t_sh_env **vars, int out);

int     cd_builtin(t_sh_cmd *cmd);

int     is_n_option(char *str);

int     echo_builtin(t_sh_cmd *command);

long    exit_atoi(char *str);

void    exit_manager(int exit_code, error_t ec, t_sh_cmd *cmd);

int     exit_builtin(t_sh_cmd *cmd);

char    *trim_pwd(char *str);

char    *sh_get_pwd(void);

int     pwd_builtin(t_sh_cmd *cmd);

char    *get_prompt_str(t_sh_env *envp);


#endif