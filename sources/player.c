/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:47:20 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/09 18:37:16 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	walk(t_game *game, int32_t x, int32_t y, char player_dir)
{
	int32_t new_player_xy[2];

	new_player_xy[0] = game->player_xy[0] + x;
	new_player_xy[1] = game->player_xy[1] + y;
	if (game->map[game->player_xy[1]][game->player_xy[0]] == KEY_EXIT)
		return ;
	if (game->map[new_player_xy[1]][new_player_xy[0]] == KEY_EXIT && count_collectibles(game) == 0)
	{
		put_picture(game->mlx, game->player_xy, 1, game->img_space);
		ft_memcpy(game->player_xy, new_player_xy, sizeof(new_player_xy));
		put_picture(game->mlx, game->player_xy, 2, game->img_space, game->img_exit_finished);
		int win_x = (game->screen_x * PIXEL) / 2 - 48;
		int win_y = (game->screen_y * PIXEL) / 2 - 48;
		mlx_image_to_window(game->mlx, game->img_win, win_x, win_y);
		return ;
	}
	if (game->map[new_player_xy[1]][new_player_xy[0]] == KEY_WALL || game->map[new_player_xy[1]][new_player_xy[0]] == KEY_EXIT)
		return ;
	game->map[new_player_xy[1]][new_player_xy[0]] = KEY_SPACE; //feld auf space setzen
	put_picture(game->mlx, game->player_xy, 1, game->img_space); //vorheriges feld auf space setzen
	ft_memcpy(game->player_xy, new_player_xy, sizeof(new_player_xy)); //player pos aktualisieren
	if (player_dir != '0')
		game->player_direction = player_dir;
	if (game->player_direction == 'R')
		put_picture(game->mlx, game->player_xy, 1, game->img_player_right); //player auf neues feld drucken
	else
		put_picture(game->mlx, game->player_xy, 1, game->img_player_left); //player auf neues feld drucken
}

void	keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game;

	game = (t_game *)param;
	if (keydata.action == MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	if (keydata.key == MLX_KEY_W)
		walk(game, 0, -1, '0');
	if (keydata.key == MLX_KEY_A)
		walk(game, -1, 0, 'L');
	if (keydata.key == MLX_KEY_S)
		walk(game, 0, 1, '0');
	if (keydata.key == MLX_KEY_D)
		walk(game, 1, 0, 'R');
}
