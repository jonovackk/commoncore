#include "../includes/libft.h"


static void	ft_manage_strings(char *s1, char *s2, char *c, int buffered)
{
	if (buffered & 0b001)
		free(s1);
	if (buffered & 0b010)
		free(s2);
	if (buffered & 0b100)
		free(c);
}

char	*ft_strjoin(char *s1, char *s2, char *c, int tofree)
{
	char	*ns;
	int		buffered;
	size_t	len1;
	size_t	len2;
	size_t	lenc;

	buffered = (!s1 + (2 * !s2)) | tofree;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (c != NULL)
		lenc = ft_strlen(c);
	else
		lenc = 0;
	ns = malloc((len1 + len2 + lenc + 1) * sizeof(char));
	if (ns == NULL)
		return (NULL);
	*ns = '\0';
	ft_strcat(ns, s1);
	if (c != NULL)
		ft_strcat(ns, c);
	ft_strcat(ns, s2);
	ft_manage_strings(s1, s2, c, buffered);
	return (ns);
}

