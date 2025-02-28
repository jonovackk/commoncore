/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:33:03 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:33:18 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Function to draws the game map on screen in the correct position
// Função para desenhar o mapa do jogo na tela na posição correta
int	ft_render_map(t_game_instance *game_init)
{
	int	rw;
	int	clmn;

	rw = -1;
	while (game_init->map_init.matrice[++rw])
	{
		clmn = 0;
		while (game_init->map_init.matrice[rw][clmn])
		{
			if (game_init->map_init.matrice[rw][clmn] == WALL)
				ft_put_img(game_init, game_init->game_objs.wall, clmn, rw);
			if (game_init->map_init.matrice[rw][clmn] == EMPTY)
				ft_put_img(game_init, game_init->game_objs.floor, clmn, rw);
			if (game_init->map_init.matrice[rw][clmn] == PLAYER)
				ft_put_img(game_init, game_init->game_objs.player, clmn, rw);
			if (game_init->map_init.matrice[rw][clmn] == COLLECTIBLE)
				ft_put_img(game_init, game_init->game_objs.collectible,
					clmn, rw);
			ft_render_exit(game_init, clmn, rw);
			clmn++;
		}
	}
	return (0);
}

void	ft_render_exit(t_game_instance *game_init, int clmn, int rw)
{
	if (game_init->map_init.matrice[rw][clmn] == EXIT)
	{
		if (game_init->game_data.collectible_count == 0)
			ft_put_img(game_init, game_init->game_objs.exit_open, clmn, rw);
		else
			ft_put_img(game_init, game_init->game_objs.exit_close, clmn, rw);
	}
}

// Function to sets the image the corresponding cell on the game board
// Função para definir a imagem da célula correspondente no tabuleiro de jogo
void	ft_put_img(t_game_instance *game_init, void *img, int wid, int hgt)
{
	mlx_put_image_to_window(game_init->mlx_ptr, game_init->win_ptr,
		img, wid * CELL_SIZE, hgt * CELL_SIZE);
}
