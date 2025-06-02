/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:32 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:05:34 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_n_option(char *str)
{
	if (!str || *str != '-')
		return (0);
	str++;
	if (!*str)
		return (0);
	while (*str == 'n')
		str++;
	return (!*str);
}

int	sh_echo_execute(t_sh_cmd *command)
{
	char	**arguments;
	char	*output_msg;
	int		print_newline;

	arguments = command->arguments + 1;
	output_msg = NULL;
	print_newline = 1;
	if (arguments)
	{
		while (*arguments && sh_n_option(*arguments))
			arguments++;
		if (arguments != command->arguments + 1)
			print_newline = 0;
		output_msg = ft_strsjoin(arguments, ft_strdup(" "), 0b10);
		ft_dprintf(command->output_fd, "%s", output_msg);
	}
	if (print_newline)
		ft_dprintf(command->output_fd, "\n");
	free(output_msg);
	return (ERR_NONE);
}
