/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:36:39 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:36:51 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Handles player movement based on keyboard input.
// - Calls ft_control_keys to process key actions.
// - Updates the player's sprite according to movement direction.
// - Calls ft_player_action to move the player in the game world.
// Trata o movimento do jogador com base na entrada do teclado.
// - Chama ft_control_keys para processar ações de teclas.
// Atualiza o sprite do jogador de acordo com a direção do movimento.
// - Chama ft_player_action para mover o jogador no mundo do jogo.
int	ft_keyboard_action(int key, t_game_instance *game_init)
{
	ft_control_keys(key, game_init);
	if (key == W || key == UP)
	{
		game_init->game_objs.player = game_init->game_objs.player_up;
		ft_player_action(game_init, 0, -1);
	}
	else if (key == A || key == LEFT)
	{
		game_init->game_objs.player = game_init->game_objs.player_left;
		ft_player_action(game_init, -1, 0);
	}
	else if (key == S || key == DOWN)
	{
		game_init->game_objs.player = game_init->game_objs.player_down;
		ft_player_action(game_init, 0, +1);
	}
	else if (key == D || key == RIGHT)
	{
		game_init->game_objs.player = game_init->game_objs.player_right;
		ft_player_action(game_init, +1, 0);
	}
	return (0);
}

// Handles special keyboard inputs.
// - Exits the game if ESC is pressed, displaying a message.
// - Restarts the game if the RESTART key is pressed.
// Trata entradas especiais do teclado.
// - Sai do jogo se ESC for pressionado, exibindo uma mensagem.
// - Reinicia o jogo se a tecla RESTART for pressionada.
int	ft_control_keys(int key, t_game_instance *game_init)
{
	if (key == ESC)
	{
		ft_printf("\nOh, is this game a little hard for you? :c\n");
		ft_close_game(game_init);
	}
	else if (key == RESTART)
		ft_reload_game(game_init);
	return (0);
}

// Auxiliary Function  : ft_events_pressed
// Função auxiliar: ft_events_pressed
void	ft_victory(t_game_instance *game_init)
{
	game_init->game_data.movements_count++;
	ft_printf("\nNice! You have found all the Grogus in the game.\n");
	ft_close_game(game_init);
}
