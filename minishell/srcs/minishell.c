#include "../includes/minishell.h"

extern int	g_exit_status;

int	is_non_empty(const char *str)
{
	const char	*tmp;

	if (!str || !*str)
		return (0);
	tmp = str;
	while (*tmp && ft_isspace(*tmp))
		tmp++;
	return (*tmp != '\0');
}
void display_logo(t_envvar *env)
{
    t_envvar *logo_var;
    int fd;
    char *line;

    logo_var = ft_get_env_var(env, "LOGOPATH");
    if (!logo_var)
        return;
    fd = open(logo_var->values[0], O_RDONLY);
    if (fd < 0)
        return;
    	printf("\033c\033[32m");
    while ((line = get_next_line(fd)) != NULL)
    {
        usleep(15000);
        ft_printf("%s", line);
        free(line);
    }
    ft_printf("\033[0m\n");
    close(fd);
}

char *generate_temp_filename(const char *prefix, int length)
{
    int urandom_fd;
    char *buffer;
    char *temp_name;
    int i;

    buffer = ft_calloc(length + 1, sizeof(char));
    if (!buffer)
        return (NULL);
    urandom_fd = open("/dev/urandom", O_RDONLY);
    if (urandom_fd < 0)
    {
        free(buffer);
        return (NULL);
    }
    read(urandom_fd, buffer, length);
    close(urandom_fd);
    for (i = 0; i < length; i++)
    {
        while (!ft_isalnum(buffer[i]))
            buffer[i] = (unsigned char)buffer[i] % 93 + 33;
    }
    temp_name = ft_strjoin(prefix, buffer, "_", 0b10);
    free(buffer);
    return (temp_name);
}

int main(int argc, char **argv, char **envp)
{
    t_envvar *env;

    rl_catch_signals = 0;
    if (argc > 1)
    {
        ft_error(ERR_INVALID_OPTION, argv[1]);
        exit(EXIT_FAILURE);
    }
    env = initialize_environment(argv, envp);
    display_logo(env);
    setup_signal_handlers();

    while (1)
    {
        update_environment(&env);
        reset_command_tree();
        handle_prompt(&env);
    }
    return (EXIT_SUCCESS);
}
