/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:35:16 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:35:36 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Function to free() and quit the program
// Função para free() e sair do programa
int	ft_close_game(t_game_instance *game_init)
{
	ft_printf("Shutting down...Thanks for playing!\n");
	ft_img_free(game_init);
	ft_map_free(game_init);
	ft_clear_resources(game_init);
	mlx_destroy_window(game_init->mlx_ptr, game_init->win_ptr);
	mlx_destroy_display(game_init->mlx_ptr);
	free(game_init->mlx_ptr);
	exit(0);
	return (0);
}

// Function to free() and reset the game (start in the same point)
// Função para free() e redefinir o jogo (iniciar no mesmo ponto)
void	ft_reload_game(t_game_instance *game_init)
{
	ft_printf("\nGame reset complete. Get ready to start again!\n");
	ft_img_free(game_init);
	ft_map_free(game_init);
	free(game_init->resolutions_init.settings_name_window);
	free(game_init->resolutions_init.settings_name_map);
	mlx_destroy_window(game_init->mlx_ptr, game_init->win_ptr);
	mlx_destroy_display(game_init->mlx_ptr);
	free(game_init->mlx_ptr);
	ft_struct_init(game_init);
	if (ft_load_map(game_init->argv_tmp[1], game_init))
	{
		ft_initialize_game(game_init);
		ft_start_game(game_init);
		mlx_loop(game_init->mlx_ptr);
	}
	else
	{
		ft_map_fail(61);
	}
}

// Function to free the name in window
// Função para liberar o nome na janela
void	ft_clear_resources(t_game_instance *game_init)
{
	if (game_init->resolutions_init.settings_name_window != NULL)
	{
		free(game_init->resolutions_init.settings_name_window);
		game_init->resolutions_init.settings_name_window = NULL;
	}
	if (game_init->resolutions_init.settings_name_map != NULL)
	{
		free(game_init->resolutions_init.settings_name_map);
		game_init->resolutions_init.settings_name_map = NULL;
	}
}
