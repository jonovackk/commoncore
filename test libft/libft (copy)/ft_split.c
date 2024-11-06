/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:48:26 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/30 09:59:36 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Counts the number of words in the string s, separated by the character c.
 */

static	unsigned int	ft_count_words(const char *s, char c)
{
	unsigned int	num_words;
	int				inside_word;

	num_words = 0;
	inside_word = 0;
	while (*s)
	{
		if (*s != c && !inside_word)
		{
			num_words++;
			inside_word = 1;
		}
		else if (*s == c)
			inside_word = 0;
		s++;
	}
	return (num_words);
}
/*
 * Allocates memory for a word and copies it from the start pointer.
 */

static char	*ft_alloc_word(const char *start, size_t len)
{
	char	*word;
	size_t	i;

	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < len)
		word[i] = start[i];
	word[i] = '\0';
	return (word);
}

/*
 * Frees allocated memory for split words.
 */

static void	ft_free_split(char **split, int i)
{
	while (i)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

/*
 * Fills the split array with words from the string s,
 * using character c as the delimiter.
 */

static char	**ft_fill_split(char **split, const char *s, char c)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c)
			{
				len++;
				s++;
			}
			split[i++] = ft_alloc_word(s - len, len);
			if (!split[i - 1])
				return (ft_free_split(split, i - 1), NULL);
		}
		else
			s++;
	}
	split[i] = NULL;
	return (split);
}

/*
 * Splits the string s into an array of words, using c as the delimiter.
 * Returns an array of strings (words) or NULL if allocation fails.
 */

char	**ft_split(const char *s, char c)
{
	unsigned int	n_words;
	char			**split;

	if (!s)
		return (NULL);
	n_words = ft_count_words(s, c);
	split = (char **)malloc((n_words + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_fill_split(split, s, c));
}
