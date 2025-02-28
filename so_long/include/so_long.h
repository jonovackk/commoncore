/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:20:33 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/26 18:56:52 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/mlx/mlx.h"
# include "../libs/libft/includes/libft.h"

# include "custom_letters.h"
# include <fcntl.h> // Read
# include <string.h> // Strerror
# include <stdio.h>

// OBJS KEYS
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define WALL '1'
# define EMPTY '0'

// KEYWORDS
# define ESC 65307
# define W 119
# define UP 65362
# define A 97
# define LEFT 65361
# define S 115
# define DOWN 65364
# define D 100
# define RIGHT 65363
# define RESTART 114

# define BUFFER_SIZE 1024
# define MAX_FILES 1

# define TRUE 1
# define FALSE 0

# define CELL_SIZE 64

// IMAGES
typedef struct s_game_objs
{
	void	*player;
	void	*player_left;
	void	*player_right;
	void	*player_down;
	void	*player_up;
	void	*collectible;
	void	*exit_open;
	void	*exit_close;
	void	*wall;
	void	*floor;
	int		img_width;
	int		img_height;
}	t_game_objs;

// POSITIONS OF PLAYER AND EXIT
typedef struct s_game_positions
{
	int	player_row;
	int	player_col;
	int	exit_row;
	int	exit_col;
}	t_game_positions;

// GAME DATA OF THE OBJECTS INSIDE THE MATRICE (INTERNAL)
typedef struct s_game_data
{
	int	player_count;
	int	exit_count;
	int	collectible_count;
	int	wall_count;
	int	empty_count;
	int	movements_count;
	int	endgame;
}	t_game_data;

// GAME RESOLUTIONS 
typedef struct s_game_resolutions
{
	int		settings_map_width;
	int		settings_map_height;
	char	*settings_name_window;
	char	*settings_name_map;
}	t_game_resolutions;

// GAME DATA OF MATRICE (EXTERN)
typedef struct s_map_data
{
	int					first_read_matrice;
	int					cols_matrice;
	int					rows_matrice;
	int					size_matrice;
	char				**matrice;
	t_game_resolutions	resolutions;
	t_game_positions	positions;
}	t_map_data;

// MAIN GAME CONTROLLER
typedef struct s_game_instance
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					argc_tmp;
	char				**argv_tmp;
	t_map_data			map_init;
	t_game_positions	positions_init;
	t_game_data			game_data;
	t_game_resolutions	resolutions_init;
	t_game_objs			game_objs;
}	t_game_instance;

// Main program initialization
//int			main(int argc, char **argv);

// Game initialization functions
void		ft_struct_init(t_game_instance *game_init);
void		ft_initialize_game(t_game_instance *game_init);

// Event handling and actions
int			ft_keyboard_action(int key, t_game_instance *game_init);
int			ft_control_keys(int key, t_game_instance *game_init);
int			ft_close_game(t_game_instance *game_init);
void		ft_reload_game(t_game_instance *game_init);

// Map validation and data handling
int			ft_load_map(char *map, t_game_instance *game_init);
int			ft_calculate_map_lines(char *map);
int			ft_line_counter(int fd);
int			ft_get_map_size(t_game_instance *game_init);
int			get_rows_count(t_game_instance *game_init);
int			get_cols_count(t_map_data *map_init);
int			ft_parse_map(int fd, t_game_instance *game_init);
int			ft_verify_map(t_game_instance *game_init);
int			ft_check_map_extension(char *map);
int			ft_map_validator(t_game_instance *game_init);
int			ft_check_map_shape(t_game_instance *game_init);
int			ft_check_wall(t_game_instance *game_init);
int			ft_object_counter(t_game_instance *game_init);
int			ft_check_map_needs(t_game_instance *game_init);

// Game actions and graphics rendering
void		ft_start_game(t_game_instance *game_init);
int			ft_player_action(t_game_instance *game_init, int clmn, int rw);
void		ft_victory(t_game_instance *game_init);
int			ft_display_moves(t_game_instance *game_init);
void		ft_track_player(t_game_instance *game_init);
void		ft_load_imgs(t_game_instance *game_init);
void		ft_test_imgs(t_game_instance *game_init, void **image, char *path);
int			ft_render_map(t_game_instance *game_init);
void		ft_render_exit(t_game_instance *game_init, int clmn, int rw);
void		ft_put_img(t_game_instance *game_init, void *img, int wid, int hgt);

// Memory cleanup and deallocation
void		ft_map_free(t_game_instance *game_init);
void		ft_img_free(t_game_instance *game_init);
void		ft_clear_resources(t_game_instance *game_init);

// Error handling
void		ft_init_fail(int n);
void		ft_map_fail(int n);

// Auxiliary functions
int			ft_strcmp(const char *s1, const char *s2);

#endif
