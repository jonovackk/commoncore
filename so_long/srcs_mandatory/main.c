/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:42:52 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:43:03 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Function to starts the game instance and initializes 
// the necessary structures
// Função para iniciar a instância do jogo e inicializar 
// as estruturas necessárias
int	main(int argc, char **argv)
{
	t_game_instance	game_init;

	ft_struct_init(&game_init);
	if (argc != 2)
		ft_map_fail(22);
	game_init.argc_tmp = argc;
	game_init.argv_tmp = argv;
	if (ft_load_map(argv[1], &game_init))
	{
		ft_initialize_game(&game_init);
		ft_start_game(&game_init);
		mlx_loop(game_init.mlx_ptr);
	}
	else
		ft_map_fail(61);
	ft_close_game(&game_init);
	return (0);
}
// Function to initialize all structs in the game 
// instance + malloc in objs
// Função para inicializar todas as estruturas na 
// instância do jogo + malloc em objs

void	ft_struct_init(t_game_instance *game_init)
{
	t_game_objs	*objs;

	*game_init = (t_game_instance){0};
	game_init->map_init.matrice = NULL;
	game_init->mlx_ptr = NULL;
	game_init->win_ptr = NULL;
	game_init->resolutions_init.settings_name_map = NULL;
	game_init->resolutions_init.settings_name_window = NULL;
	objs = malloc(sizeof(t_game_objs));
	if (objs == NULL)
		ft_map_fail(12);
	game_init->game_objs = *objs;
	free (objs);
	return ;
}
