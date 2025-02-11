/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:36:45 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/11 12:42:58 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	pos;

	if (!map)
		return ;
	pos = 0;
	while (map[pos])
	{
		free(map[pos]);
		map[pos] = NULL;
		pos++;
	}
	free(map);
}

int	count_collectibles(char **map)
{
	int32_t	x;
	int32_t	y;
	int		number_coll;

	number_coll = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == KEY_COLL)
				number_coll++;
			x++;
		}
		y++;
	}
	return (number_coll);
}

void	set_player_coords(t_game *game)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == KEY_PLAYER)
			{
				game->player_xy[0] = x;
				game->player_xy[1] = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	set_window_size(t_game *game)
{
	int	i;

	game->screen_x = ft_strlen(game->map[0]);
	i = 0;
	while (game->map[i] != NULL && game->map[i][0] == '1')
	{
		i++;
	}
	game->screen_y = i;
}

void	split_into_maps(t_game *game, char *map_string)
{
	game->map = ft_split(map_string, '\n');
	game->flood_map = ft_split(map_string, '\n');
	if (!game->map || !game->flood_map)
		error_split_failed(game, map_string);
}
