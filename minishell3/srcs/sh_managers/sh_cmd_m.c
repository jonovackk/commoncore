#include "../../includes/minishell.h"

char	*sh_find_path(char *cmd, t_sh_env *env)
{
	int		i;
	char	*path;
	char	*bin;

	if (!cmd)
		return (ft_strdup(""));
	if (!*cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (env && ft_strncmp(env->key, "PATH", 5))
		env = env->next;
	if (!env)
		return (ft_strjoin("/", ft_strdup(cmd), NULL, 0b10));
	bin = ft_strjoin("/", cmd, 0, 0b00);
	i = 0;
	path = ft_strjoin(env->values[i++], bin, 0, 0);
	while (env->values[i] && access(path, X_OK) == -1)
	{
		free(path);
		path = ft_strjoin(env->values[i++], bin, 0, 0);
	}
	free(bin);
	return (path);
}

void	sh_free_cmd(t_sh_cmd *cmd)
{
	ft_clear_redir_list(cmd->redirects);
	free(cmd->executable);
	ft_free_tab((void **)cmd->arguments);
	free(cmd);
}