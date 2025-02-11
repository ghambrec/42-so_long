/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:42:10 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/11 11:43:09 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textures(t_textures *textures)
{
	textures->space = mlx_load_png(PNG_SPACE);
	if (!textures->space)
		perror_exit_mlx("Could not load space png");
	textures->wall = mlx_load_png(PNG_WALL);
	if (!textures->wall)
		perror_exit_mlx("Could not load wall png");
	textures->coll = mlx_load_png(PNG_COLL);
	if (!textures->coll)
		perror_exit_mlx("Could not load collectible png");
	textures->exit = mlx_load_png(PNG_EXIT_START);
	if (!textures->exit)
		perror_exit_mlx("Could not load exit png");
	textures->exit_finished = mlx_load_png(PNG_EXIT_FINISH);
	if (!textures->exit_finished)
		perror_exit_mlx("Could not load exit_finished png");
	textures->player_right = mlx_load_png(PNG_PLAYER_RIGHT);
	if (!textures->player_right)
		perror_exit_mlx("Could not load player_right png");
	textures->player_left = mlx_load_png(PNG_PLAYER_LEFT);
	if (!textures->player_left)
		perror_exit_mlx("Could not load player_left png");
	textures->win = mlx_load_png(PNG_WIN);
	if (!textures->win)
		perror_exit_mlx("Could not load win png ");
}

void	load_images(t_game *game, t_textures *textures)
{
	game->img_space = mlx_texture_to_image(game->mlx, textures->space);
	game->img_wall = mlx_texture_to_image(game->mlx, textures->wall);
	game->img_coll = mlx_texture_to_image(game->mlx, textures->coll);
	game->img_exit = mlx_texture_to_image(game->mlx, textures->exit);
	game->img_exit_finished = mlx_texture_to_image(\
										game->mlx, textures->exit_finished);
	game->img_player_right = mlx_texture_to_image(\
										game->mlx, textures->player_right);
	game->img_player_left = mlx_texture_to_image(\
										game->mlx, textures->player_left);
	game->img_win = mlx_texture_to_image(game->mlx, textures->win);
	mlx_delete_texture(textures->space);
	mlx_delete_texture(textures->wall);
	mlx_delete_texture(textures->coll);
	mlx_delete_texture(textures->exit);
	mlx_delete_texture(textures->exit_finished);
	mlx_delete_texture(textures->player_right);
	mlx_delete_texture(textures->player_left);
	mlx_delete_texture(textures->win);
	if (mlx_errno != 0)
		perror_exit_mlx("Failed ot load texture into image!");
}

void	put_picture(mlx_t *mlx, int32_t xy[2], int c, ...)
{
	va_list		imgs;
	mlx_image_t	*img;

	va_start(imgs, c);
	while (c > 0)
	{
		img = va_arg(imgs, mlx_image_t *);
		if (img)
			mlx_image_to_window(mlx, img, xy[0] * PIXEL, xy[1] * PIXEL);
		c--;
	}
	va_end(imgs);
}
