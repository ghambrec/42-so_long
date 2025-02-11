/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:56:14 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/11 13:05:38 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define PROGRAM_NAME "Super Mario"
# define PIXEL 32

# define KEY_SPACE '0'
# define KEY_WALL '1'
# define KEY_COLL 'C'
# define KEY_EXIT 'E'
# define KEY_PLAYER 'P'

# define PNG_SPACE "./textures/green_32.png"
# define PNG_WALL "./textures/brick_32.png"
# define PNG_COLL "./textures/star_in_32.png"
# define PNG_EXIT_START "./textures/flag_start.png"
# define PNG_EXIT_FINISH "./textures/flag_finish.png"
# define PNG_PLAYER_RIGHT "./textures/mario_right.png"
# define PNG_PLAYER_LEFT "./textures/mario_left.png"
# define PNG_WIN "./textures/win.png"

# include "../lib/myLibft/include/my_libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <errno.h>

typedef struct s_textures
{
	mlx_texture_t	*space;
	mlx_texture_t	*wall;
	mlx_texture_t	*coll;
	mlx_texture_t	*exit;
	mlx_texture_t	*exit_finished;
	mlx_texture_t	*player_right;
	mlx_texture_t	*player_left;
	mlx_texture_t	*win;
}	t_textures;

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	char		**flood_map;
	int			flood_exit;
	int			flood_colls;
	int32_t		screen_x;
	int32_t		screen_y;
	int32_t		player_xy[2];
	char		player_direction;
	int			number_moves;
	mlx_image_t	*img_space;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_coll;
	mlx_image_t	*img_exit;
	mlx_image_t	*img_exit_finished;
	mlx_image_t	*img_player_right;
	mlx_image_t	*img_player_left;
	mlx_image_t	*img_win;
}	t_game;

// HELPER
void	free_map(char **map);
int		count_collectibles(char **map);
void	set_player_coords(t_game *game);
void	set_window_size(t_game *game);
void	split_into_maps(t_game *game, char *map_string);

// MAP
void	get_map(char *map_name, t_game *game);
void	map_init(t_game *game);
void	create_game_map(t_game *game, t_textures *textures);

// ERROR-HANDLING
void	perror_exit_mlx(char *error_msg);
void	validate_error(char *error_msg, t_game *game, char *map_string);
void	error_open_map(void);
void	error_empty_map_file(void);
void	error_split_failed(t_game *game, char *map_string);

// TEXTURES
void	load_textures(t_textures *textures);
void	load_images(t_game *game, t_textures *textures);
void	put_picture(mlx_t *mlx, int32_t xy[2], int c, ...);

// PLAYER
void	walk(t_game *game, int32_t x, int32_t y, char player_dir);
void	keyhook(mlx_key_data_t keydata, void *param);

// MAP VALIDATION
void	map_validation(t_game *game, char *map_string);
void	validate_characters(t_game *game, char *map_string);
void	validate_rectangular(t_game *game, char *map_string);
void	validate_surrounding(t_game *game, char *map_string);
void	validate_path(t_game *game, char *map_string);

#endif