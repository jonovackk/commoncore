#include "libft.h"

void	ft_free_tab(void **tab)
{
	void	**tmp;

	tmp = tab;
	if (!tab || !tmp)
		return ;
	while (*tmp)
		free(*(tmp++));
	free(tab);
}

void	ft_free_big_tab(void **tab, int depth)
{
	void	**tmp;

	tmp = tab;
	if (!tab)
		return ;
	if (depth == 1)
	{
		free(tab);
		return ;
	}
	while (*tmp)
		ft_free_big_tab((void **)*(tmp++), depth - 1);
	free(tab);
}