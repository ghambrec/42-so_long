/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:03:25 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/10 18:46:37 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	floodfill(int x, int y, t_game *game)
{
	if (game->flood_map[y][x] == KEY_WALL || game->flood_map[y][x] == 'X')
		return ;
	if (game->flood_map[y][x] == KEY_EXIT)
	{
		game->flood_exit = true;
		return ;	
	}
	if (game->flood_map[y][x] == KEY_COLL)
		game->flood_colls++;
	game->flood_map[y][x] = 'X';
	floodfill(x, y + 1, game);
	floodfill(x, y - 1, game);
	floodfill(x + 1, y, game); 
	floodfill(x - 1, y, game); 
}

void	validate_path(t_game *game, char *map_string)
{
	floodfill(game->player_xy[0], game->player_xy[1], game);
	if (count_collectibles(game->map) != game->flood_colls)
		validate_error("Collectible not reachable!", game, map_string);
	if (game->flood_exit == false)
		validate_error("Exit not reachable!", game, map_string);
}
