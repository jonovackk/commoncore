/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:37:05 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:37:24 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Function to initializes the window and sets the init
// properties of the game
// Função para inicializar a janela e definir as propriedades 
// de inicialização do jogo
void	ft_initialize_game(t_game_instance *game_init)
{
	game_init->mlx_ptr = mlx_init();
	if (game_init->mlx_ptr == NULL)
		ft_init_fail(38);
	game_init->game_data.movements_count = 0;
	ft_load_imgs(game_init);
	game_init->game_objs.player = game_init->game_objs.player_down;
	game_init->win_ptr = mlx_new_window(game_init->mlx_ptr,
			game_init->map_init.resolutions.settings_map_width
			* CELL_SIZE, game_init->map_init.resolutions.settings_map_height
			* CELL_SIZE, "The Mando");
	if (game_init->win_ptr == NULL)
		ft_init_fail(38);
}
// Function to loads the different game images from image files 
// (XPM format) using Minilibx
// Função para carregar as diferentes imagens do jogo a partir 
// de arquivos de imagem (formato XPM) usando o Minilibx

void	ft_load_imgs(t_game_instance *game_init)
{
	ft_test_imgs(game_init, &game_init->game_objs.player_up,
		"rscs/textures/Player/mando_up.xpm");
	ft_test_imgs(game_init, &game_init->game_objs.player_down,
		"rscs/textures/Player/mando_down.xpm");
	ft_test_imgs(game_init, &game_init->game_objs.player_right,
		"rscs/textures/Player/mando_right.xpm");
	ft_test_imgs(game_init, &game_init->game_objs.player_left,
		"rscs/textures/Player/mando_left.xpm");
	ft_test_imgs(game_init, &game_init->game_objs.collectible,
		"rscs/textures/Collectibles/grogu.xpm");
	ft_test_imgs(game_init, &game_init->game_objs.floor,
		"rscs/textures/Tiles/midBlocks_02.xpm");
	ft_test_imgs(game_init, &game_init->game_objs.exit_open,
		"rscs/textures/Exit/exit_open_01.xpm");
	ft_test_imgs(game_init, &game_init->game_objs.exit_close,
		"rscs/textures/Exit/exit_close_01.xpm");
	ft_test_imgs(game_init, &game_init->game_objs.wall,
		"rscs/textures/Tiles/blockSimple.xpm");
}

// Checks that the images have been uploaded correctly.
// Verifica se as imagens foram carregadas corretamente.
void	ft_test_imgs(t_game_instance *game_init, void **image, char *path)
{
	int	wdth;
	int	hght;

	*image = mlx_xpm_file_to_image(game_init->mlx_ptr, path, &wdth, &hght);
	if (*image == NULL)
	{
		ft_init_fail(1);
		ft_close_game(game_init);
	}
}
