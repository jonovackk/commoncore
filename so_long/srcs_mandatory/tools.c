/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:43:12 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/31 17:40:50 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Function to compares two strings character by character and returns the
//difference between the first two non-matching characters (in ASCII value)
// Função para comparar duas cadeias de caracteres, caractere 
// por caractere, e retorna a
// diferença entre os dois primeiros caracteres não correspondentes
// (em valor ASCII)
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
