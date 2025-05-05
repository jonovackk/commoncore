#include "minishell.h"

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
	char	*tmp;
	char	*chr;

	chr = ft_strrchr(str, c);
	tmp = NULL;
	if (chr && *chr && *(chr + 1))
		tmp = ft_strndup(chr + 1, ft_strlen(str) - (chr - str));
	return (tmp);
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