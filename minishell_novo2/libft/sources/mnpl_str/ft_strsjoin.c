/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:01:04 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/28 14:21:46 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_manage_strings(char **strs, char *sep, int tf)
{
	if (tf & 0b01)
		ft_free_tab((void **) strs);
	if (tf & 0b10)
		free(sep);
}

static char	*ft_manage_join(char **strs, char **sep, int *tofree)
{
	if (!*sep)
	{
		*tofree |= 0b10;
		*sep = ft_strdup("");
	}
	if (!strs)
	{
		if (*tofree & 0b10)
			free(*sep);
		return (NULL);
	}
	if (!*strs)
	{
		if (*tofree & 0b10)
			free(*sep);
		return (ft_strdup(""));
	}
	return (*sep);
}

char	*ft_strsjoin(char **strs, char *sep, int tofree)
{
	char	**tmp;
	char	*check;
	char	*ns;
	int		len;

	check = ft_manage_join(strs, &sep, &tofree);
	if (check != sep)
		return (check);
	tmp = strs;
	len = 1;
	while (*tmp)
		len += ft_strlen(*(tmp++));
	ns = malloc((len + (ft_tab_len(strs) - 1) * ft_strlen(sep)) * sizeof(char));
	if (!ns)
		return (NULL);
	*ns = 0;
	tmp = strs;
	while (*tmp)
	{
		ft_strcat(ns, *(tmp++));
		if (*tmp)
			ft_strcat(ns, sep);
	}
	ft_manage_strings(strs, sep, tofree);
	return (ns);
}
