/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins_h.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:08 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:05:15 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_numeric(char *str)
{
	int		sign;
	char	*tmp;

	sign = 0;
	tmp = str;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		str++;
		sign = 1;
	}
	while (ft_isdigit(*(str)))
		str++;
	if (sign)
		return (!*str && str - tmp < 19);
	return (!*str && (str - tmp) && (str - tmp < 18));
}

char	*ft_backtrim(char *str, char c)
{
	char	*chr;

	if (!str)
		return (NULL);
	chr = ft_strrchr(str, c);
	if (!chr || !*(chr + 1))
		return ft_strdup(str);
	return ft_strdup(chr + 1);
}

char	**ft_strtab(char *str)
{
	char	**tab;

	tab = malloc(2 * sizeof(char *));
	*tab = str;
	*(tab + 1) = NULL;
	return (tab);
}

void	ft_str_tabjoin(char ***tab, char **next)
{
	char	**tmp;

	tmp = next;
	if (!tmp)
		return ;
	while (*tmp)
		ft_strapp(tab, *(tmp++));
	free(next);
}

void	ft_strapp(char ***tab, char *str)
{
	char	**tmp;
	char	**ttmp;
	char	**res;

	tmp = *tab;
	while (tmp && *tmp)
		tmp++;
	res = malloc((tmp - *tab + 2) * sizeof(char *));
	tmp = *tab;
	ttmp = res;
	while (tmp && *tmp)
		*(ttmp++) = *(tmp++);
	*(ttmp++) = str;
	*ttmp = 0;
	free(*tab);
	*tab = res;
}