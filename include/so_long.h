/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:56:14 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/05 14:53:30 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define PROGRAM_NAME "so_long"
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
// # define PNG_PLAYER_LEFT "./textures/mario_left.png"

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
	mlx_texture_t	*player;
}	t_textures;

// typedef struct s_img
// {
// 	mlx_image_t	*space;
// 	mlx_image_t	*wall;
// 	mlx_image_t	*coll;
// 	mlx_image_t	*exit;
// 	mlx_image_t	*player;
// }	t_img;

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	int32_t		screen_x;
	int32_t		screen_y;
	int32_t		player_xy[2];
	int			number_moves;
	mlx_image_t	*img_space;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_coll;
	mlx_image_t	*img_exit;
	mlx_image_t	*img_exit_finished;
	mlx_image_t	*img_player;
}	t_game;

#endif