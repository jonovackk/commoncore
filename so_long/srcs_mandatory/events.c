/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:35:51 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:36:06 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Sets up event hooks and starts the game loop.
// - Handles window close and keyboard input events.
// - Calls ft_render_map continuously to update the game.
// Configura ganchos de eventos e inicia o loop do jogo.
// Trata os eventos de fechamento de janela e entrada de teclado.
// - Chama o ft_render_map continuamente para atualizar o jogo.
void	ft_start_game(t_game_instance *game_init)
{
	mlx_hook(game_init->win_ptr, 17, 0, ft_close_game, game_init);
	mlx_hook(game_init->win_ptr, 2, (1L << 0), ft_keyboard_action, game_init);
	mlx_loop_hook(game_init->mlx_ptr, &ft_render_map, game_init);
}

// Function to prints the current number of movements on the terminal
// Função para imprimir o número atual de movimentos no terminal
int	ft_display_moves(t_game_instance *game_init)
{
	static int	previous_count_movements;
	int			current_count_movements;

	previous_count_movements = -1;
	current_count_movements = game_init->game_data.movements_count;
	if (current_count_movements != previous_count_movements)
	{
		ft_printf("You moved %d times.\n", current_count_movements);
		previous_count_movements = current_count_movements;
	}
	return (1);
}

// Handles player movement and interactions.
// - Moves the player if the destination is valid.
// - Collects items and updates counters.
// - Triggers victory if conditions are met.
// Trata do movimento e das interações do jogador.
// Move o jogador se o destino for válido.
// Coleta itens e atualiza contadores.
// Aciona a vitória se as condições forem atendidas.
int	ft_player_action(t_game_instance *game_init, int clmn, int rw)
{
	int	new_row;
	int	new_col;
	int	current_tile;

	ft_track_player(game_init);
	new_row = game_init->positions_init.player_row + rw;
	new_col = game_init->positions_init.player_col + clmn;
	current_tile = game_init->map_init.matrice[new_row][new_col];
	if (current_tile == EMPTY || current_tile == COLLECTIBLE)
	{
		game_init->map_init.matrice[new_row][new_col] = PLAYER;
		game_init->map_init.matrice[game_init->positions_init.player_row]
		[game_init->positions_init.player_col] = EMPTY;
		game_init->positions_init.player_row = new_row;
		game_init->positions_init.player_col = new_col;
		if (current_tile == COLLECTIBLE)
			game_init->game_data.collectible_count--;
		game_init->game_data.movements_count++;
	}
	else if (current_tile == EXIT
		&& game_init->game_data.collectible_count == 0)
		ft_victory(game_init);
	return (ft_display_moves(game_init));
}

// Function to finds the player position and performs actions like moving the
// player or removing a collectible based on the block they're trying to move
// to after the player presses a key
// Função para encontrar a posição do jogador e executar ações como mover o
// jogador ou remover um colecionável com base no bloco
// para o qual ele está tentando se mover
// depois que o jogador pressiona uma tecla
void	ft_track_player(t_game_instance *game_init)
{
	int	cl;
	int	rw;

	rw = 0;
	while (game_init->map_init.matrice[rw] != NULL)
	{
		cl = 0;
		while (game_init->map_init.matrice[rw][cl] != '\0')
		{
			if (game_init->map_init.matrice[rw][cl] == PLAYER)
			{
				game_init->positions_init.player_row = rw;
				game_init->positions_init.player_col = cl;
				return ;
			}
			cl++;
		}
		rw++;
	}
}
