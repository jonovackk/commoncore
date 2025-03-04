#include "../../includes/minishell.h"

char	*resolve_exec_path(char *command, t_variable *env_vars)
{
	int		i;
	char	*exec_path;
	char	*prefixed_cmd;

	if (!command)
		return (ft_strdup(""));
	if (!*command || ft_strchr(command, '/'))
		return (ft_strdup(command));
	while (env_vars && ft_strncmp(env_vars->name, "PATH", 5))
		env_vars = env_vars->next;
	if (!env_vars)
		return (ft_strjoin("/", ft_strdup(command), NULL, 0b10));
	prefixed_cmd = ft_strjoin("/", command, 0, 0b00);
	i = 0;
	exec_path = ft_strjoin(env_vars->values[i++], prefixed_cmd, 0, 0);
	while (env_vars->values[i] && access(exec_path, X_OK) == -1)
	{
		free(exec_path);
		exec_path = ft_strjoin(env_vars->values[i++], prefixed_cmd, 0, 0);
	}
	free(prefixed_cmd);
	return (exec_path);
}

void	delete_instruction(t_instruction *instr)
{
	ft_clear_redir_list(instr->redirections);
	free(instr->cmd_path);
	ft_free_tab((void **)instr->arguments);
	free(instr);
}
