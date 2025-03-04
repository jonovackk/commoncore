#ifndef FT_DATA_STRUCTURES_H
# define FT_DATA_STRUCTURES_H

typedef struct  s_lex
{
    char                *str;
    t_lex_type          type;
    struct s_lex        *next;
    struct s_lex        *prev;
}   t_lex;

typedef struct      s_variable
{
    char                *name;
    char                **values;
    struct s_variable   *next;
}   t_variable;

typedef struct s_redirect
{
    t_redirect_type     type;
    char                *file;
    struct s_redirect   *next; 
}   t_redirect;

typedef struct s_instruction
{
    int             in_fd;
    int             out_fd;
    int             heredoc_fd;
    char            *cmd_path;
    char            **arguments;
    t_redirect      *redirections;
    t_variable      **env_vars;
}   t_instruction;

typedef struct s_tree_node
{
    t_instruction       *instruction;
    t_lex               *lexeme;
    struct s_tree_node  *left_child;
    struct s_tree_node  *right_child;
}t_tree_node;

typedef struct  s_variable
{
    char                *name;
    struct s_redir      **values;
    struct s_variable   *next;
}   t_variable;

typedef struct s_redirect
{
    t_redirect_type     type;
    char                *file;
    struct s_redirect   *next;
}t_redirect;

typedef struct s_command
{
    int             in_fd;
    int             out_fd;
    int             heredoc_fd;
    char            *cmd_path;
    char            **args;
    t_redirect         *redirections;
    t_variable        **env_vars;
}   t_command;


//shell_data_structure
//builders.c
t_lex           *create_lexeme(char *str, t_lex_type type);
t_variable      *create_variable(char *value);
t_instruction   *create_instruction(t_redirect *redirections, char **arguments, t_variable **env_vars);
char            *ft_get_path(char *cmd, t_variable *env_vars);
t_tree_node     *create_tree_node(t_instruction instruction, t_lex *lexeme);

//command.c
char            *ft_resolve_exec_path(char *cmd, t_variable *envp);
void            ft_delete_command(t_command *cmd);
void            ft_clear_redir_list(t_redirect *redir);

//variables.c
void            add_variable(t_variable **variables, t_variable *variable);
void            remove_variable(t_variable **variables, char *name);
void            delete_variable(t_variable *variable);
void            clear_variables(t_variable *variables);

//variables_utils.c
void            set_variable(t_variable **vars, char *name, char *value);
void            append_variable(t_variable **vars, char *name, char *value);
t_variable      *get_variable(t_variable *vars, char *name);
t_variable      *get_last_variable(t_variable *vars);

#endif