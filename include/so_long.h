/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:56:14 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/04 18:53:51 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define PROGRAM_NAME "so_long"
# define PIXEL 32


# define PNG_SPACE "./textures/grass.png"
# define PNG_WALL "./textures/"
# define PNG_COLLECTIBLE "./textures/"
# define PNG_EXIT "./textures/"
# define PNG_PLAYER "./textures/"

# include "../lib/myLibft/include/my_libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <errno.h>

typedef struct s_textures
{
	mlx_texture_t	*space;
	mlx_texture_t	*wall;
	mlx_texture_t	*collectible;
	mlx_texture_t	*exit;
	mlx_texture_t	*player;
}	t_textures;

typedef struct s_img
{
	mlx_image_t	*space;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*player;
}	t_img;

typedef struct s_game
{
	mlx_t	*mlx;
	char	**map;
	int		horizontal;
	int		vertical;
	int		number_moves;
}	t_game;

#endif