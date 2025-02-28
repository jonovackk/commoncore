/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issues.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:33:27 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:34:24 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Function to return feedback for errors during 
// game initialization
// Função para retornar feedback sobre erros durante
//  a inicialização do jogo
void	ft_init_fail(int n)
{
	if (n == 38)
		ft_printf("Error\n%s",
			"Unable to initialize due to library mismatch!\n",
			COLOR_RED);
	else if (n == 1)
		ft_printf("Error\n%s",
			"Permission Denied\n",
			"The operation cannot be performed!\n",
			COLOR_RED);
	else if (n == 2)
		ft_printf("Error\n%s",
			"File System Error\n",
			"Target file or directory does not exist!\n",
			COLOR_RED);
	exit(n);
}

// Function to return feedback for errors related to the map
// Função para retornar feedback sobre erros relacionados ao mapa
void	ft_map_fail(int n)
{
	if (n == 21)
		ft_printf("Error\n%s",
			"Invalid Input:\n",
			"A directory was provided instead of a map file.\n",
			COLOR_RED);
	else if (n == 22 || n == 52 || n == 59 || n == 24 || n == 5)
		ft_printf("Error\n%s",
			"The correct format is: ./so_long <filename>.ber\n",
			COLOR_RED);
	else if (n == 61)
		ft_printf("Error:\n%s",
			"The provided map is not valid. Please check and try again.\n",
			COLOR_RED);
	else if (n == 63)
		ft_printf("Error\n%s",
			"The player, collectibles, or exit is inaccessible!\n",
			COLOR_RED);
	exit(n);
}
