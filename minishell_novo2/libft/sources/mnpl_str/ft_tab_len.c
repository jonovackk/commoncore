#include "libft.h"

int	ft_tab_len(char **tab)
{
	char	**tmp;

	tmp = tab;
	while (tmp && *(tmp))
		tmp++;
	return (tmp - tab);
}