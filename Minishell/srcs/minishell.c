/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:57 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:08:58 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_shell_exit_status;

int	is_non_empty(const char *str)
{
	const char	*tmp;

	if (!str || !*str)
		return (0);
	tmp = str;
	while (*tmp && isspace(*tmp))
		tmp++;
	return (*tmp != '\0');
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
    temp_name = ft_strjoin((char *)prefix, buffer, "_", 0b10);
    
    return (temp_name);
}

static t_sh_env	*init_shell(int argc, char **argv, char **envp)
{
	t_sh_env	*env;

	rl_catch_signals = 0;
	if (argc > 1)
	{
		sh_display_error(ERR_INVALID_OPTION, argv[1]);
		exit(EXIT_FAILURE);
	}
	env = sh_env_init(argv, envp);
	if (!env)
	{
		sh_display_error(ERR_FAIL_GENERAL,
			"Failed to initialize environment");
		exit(EXIT_FAILURE);
	}
	sh_configure_signal_state(HANDLER_IGN);
	return (env);
}

static void		main_loop(t_sh_env **env)
{
	t_sh_env	*current_env;
	int			saved_stdin;
	int			saved_stdout;

	while (1)
	{
		current_env = sh_env_context(env);
		if (!current_env)
		{
			sh_display_error(ERR_FAIL_GENERAL,
				"Environment context lost");
			exit(EXIT_FAILURE);
		}
		sh_command_tree_state(1, NULL);
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		sh_handle_prompt(env);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_sh_env	*env;

	env = init_shell(argc, argv, envp);
	main_loop(&env);
	return (EXIT_SUCCESS);
}

