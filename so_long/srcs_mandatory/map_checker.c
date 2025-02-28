/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:41:41 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:41:51 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Function to checks if the map is valid by calling three other
// functions and returning 1 if all are true, 0 otherwise
// Função para verificar se o mapa é válido, chamando três outras
// funções e retornando 1 se todas forem verdadeiras e 0 caso contrário.
int	ft_map_validator(t_game_instance *game_init)
{
	if (!(ft_object_counter(game_init)))
		return (0);
	if (!(ft_check_map_shape(game_init)))
		return (0);
	if (!(ft_check_wall(game_init)))
		return (0);
	return (1);
}

// Function to check if the map has a valid rectangular shape
// Função para verificar se o mapa tem uma forma retangular válida
int	ft_check_map_shape(t_game_instance *game_init)
{
	if (game_init->map_init.cols_matrice <= 0
		|| game_init->map_init.rows_matrice <= 0)
		return (0);
	if (game_init->map_init.size_matrice % game_init->map_init.rows_matrice == 0
		&& game_init->map_init.size_matrice / game_init->map_init.rows_matrice
		== game_init->map_init.cols_matrice)
		return (1);
	return (0);
}

// Function to check if the map is fully enclosed by walls
// Função para verificar se o mapa está totalmente delimitado por paredes
int	ft_check_wall(t_game_instance *game_init)
{
	int		i;
	int		j;

	i = 0;
	while (i < game_init->map_init.rows_matrice)
	{
		j = 0;
		while (j < game_init->map_init.cols_matrice)
		{
			if (i == 0 || j == 0 || i == game_init->map_init.rows_matrice
				- 1 || j == game_init->map_init.cols_matrice - 1)
			{
				if (game_init->map_init.matrice[i][j] != WALL)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// Function to counts the different types of objects in the map
// If it finds an invalid character, it returns: invalid map
// Função para contar os diferentes tipos de objetos no mapa
// se encontrar caractere invalido, retorna: mapa invalido 

int	ft_object_counter(t_game_instance *game_init)
{
	int	rw;
	int	clmn;

	rw = -1;
	while (game_init->map_init.matrice[++rw])
	{
		clmn = 0;
		while (game_init->map_init.matrice[rw][clmn])
		{
			if (game_init->map_init.matrice[rw][clmn] == PLAYER)
				game_init->game_data.player_count++;
			else if (game_init->map_init.matrice[rw][clmn] == EXIT)
				game_init->game_data.exit_count++;
			else if (game_init->map_init.matrice[rw][clmn] == COLLECTIBLE)
				game_init->game_data.collectible_count++;
			else if (game_init->map_init.matrice[rw][clmn] == WALL)
				game_init->game_data.wall_count++;
			else if (game_init->map_init.matrice[rw][clmn] == EMPTY)
				game_init->game_data.empty_count++;
			else if (game_init->map_init.matrice[rw][clmn] != '\n')
				return (0);
			clmn++;
		}
	}
	return (ft_check_map_needs(game_init));
}

// Check that the map meets the game's minimum requirements.
// If it has 1 player/1 exit/1 collectible
// Verifica se o mapa atende aos requisitos mínimos do jogo. 
// Se tem 1  jogador/1saida/1 coletavel

int	ft_check_map_needs(t_game_instance *game_init)
{
	if (!(game_init->game_data.player_count == 1
			&& game_init->game_data.exit_count == 1
			&& game_init->game_data.collectible_count >= 1))
		return (0);
	return (1);
}
