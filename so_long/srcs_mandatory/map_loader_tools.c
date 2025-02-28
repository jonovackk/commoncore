/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:41:18 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:41:27 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Function to calculate the dimensions of the game map by counting
// the number of rows, columns and matrice
// Função para calcular as dimensões do mapa do jogo contando
// o número de linhas, colunas e matrizes
int	ft_get_map_size(t_game_instance *game_init)
{
	game_init->map_init.cols_matrice = get_cols_count(&game_init->map_init);
	if (game_init->map_init.cols_matrice == 0)
		return (0);
	return (get_rows_count(game_init));
}

int	get_cols_count(t_map_data *map_init)
{
	char	*rw;
	int		cls_count;

	rw = map_init->matrice[0];
	cls_count = 0;
	while (*rw && *rw != '\n')
	{
		cls_count++;
		rw++;
	}
	return (cls_count);
}

int	get_rows_count(t_game_instance *game_init)
{
	int	rw_index;
	int	rw_len;

	rw_index = 0;
	while (game_init->map_init.matrice[rw_index])
	{
		rw_len = ft_strlen(game_init->map_init.matrice[rw_index]);
		if (rw_len > 0 && game_init->map_init.matrice[rw_index]
			[rw_len - 1] == '\n')
			rw_len--;
		if (rw_len != game_init->map_init.cols_matrice)
		{
			game_init->map_init.rows_matrice = 0;
			return (0);
		}
		game_init->map_init.rows_matrice++;
		rw_index++;
	}
	game_init->map_init.size_matrice = game_init->map_init.rows_matrice
		* game_init->map_init.cols_matrice;
	game_init->map_init.resolutions.settings_map_width
		= game_init->map_init.cols_matrice;
	game_init->map_init.resolutions.settings_map_height
		= game_init->map_init.rows_matrice;
	return (1);
}

// Function to check if the file has the extension “.ber” and if it 
// meets the necessary criteria.
// Função para verificar se o arquivo tem a extensão ".ber" 
// e se atende aos critérios necessários.
int	ft_check_map_extension(char *map)
{
	char		*extension;
	char		*file_extension;
	static int	file_count;

	file_count = 0;
	extension = ".ber";
	file_extension = ft_strrchr(map, '.');
	if (map[ft_strlen(map) - 1] == '/')
	{
		ft_map_fail(21);
		return (0);
	}
	else if (!file_extension || !ft_strcmp(file_extension, ""))
		return (0);
	else if (file_extension && !ft_strcmp(file_extension, extension))
	{
		if (file_count >= MAX_FILES)
			return (0);
		file_count++;
	}
	else
		return (0);
	return (1);
}
