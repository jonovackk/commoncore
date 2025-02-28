/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:40:49 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/27 15:41:05 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "../libs/libft/includes/libft.h"

// Function to open and read the map file
// Função para abrir e ler o arquivo do mapa
int	ft_load_map(char *map, t_game_instance *game_init)
{
	int	fd;

	if (!ft_check_map_extension(map))
		return (ft_map_fail(22), 0);
	if (!ft_calculate_map_lines(map))
		return (0);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (0);
	game_init->map_init.first_read_matrice = ft_calculate_map_lines(map);
	if (!game_init->map_init.first_read_matrice
		|| game_init->map_init.first_read_matrice < 3)
	{
		close (fd);
		ft_map_free(game_init);
		return (0);
	}
	if (!ft_parse_map(fd, game_init))
	{
		close(fd);
		ft_map_free(game_init);
		return (0);
	}
	close(fd);
	return (1);
}

// Function to count the map content for ft_calloc
// (reserved space to ft_read_map() function)
// Função para contar o conteúdo do mapa para ft_calloc
// (espaço reservado para a função ft_read_map())
int	ft_calculate_map_lines(char *map)
{
	int	fd;
	int	count;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (-1);
	count = ft_line_counter(fd);
	if (close(fd) == -1)
		return (-1);
	return (count);
}

int	ft_line_counter(int fd)
{
	int		count;
	char	buffer[BUFFER_SIZE];
	ssize_t	n_read;
	int		i;

	count = 0;
	while (1)
	{
		n_read = read(fd, buffer, BUFFER_SIZE);
		if (n_read < 0)
			return (0);
		if (n_read == 0)
			break ;
		i = 0;
		while (i < n_read)
		{
			if (buffer[i] == '\n')
				count++;
			i++;
		}
	}
	count++;
	return (count);
}

// Function to reads a map from a file, validates it, and sets
// it in the game instance
// Função para ler um mapa de um arquivo, validá-lo e defini-lo
// na instância do jogo.
int	ft_parse_map(int fd, t_game_instance *game_init)
{
	int		i;
	char	*buffer;

	game_init->map_init.matrice
		= ft_calloc(game_init->map_init.first_read_matrice + 1, sizeof(char *));
	if (!game_init->map_init.matrice)
	{
		ft_map_free(game_init);
		return (0);
	}
	i = 0;
	buffer = NULL;
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		game_init->map_init.matrice[i] = buffer;
		i++;
	}
	if (!ft_verify_map(game_init))
		return (0);
	return (1);
}

int	ft_verify_map(t_game_instance *game_init)
{
	if (game_init->map_init.matrice[0] == NULL
		|| !ft_get_map_size(game_init) || !ft_map_validator(game_init))
	{
		ft_map_free(game_init);
		return (0);
	}
	return (1);
}
