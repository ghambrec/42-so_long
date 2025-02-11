/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:24:04 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/11 12:47:00 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_map(char *map_name, t_game *game)
{
	int		fd;
	char	*new_line;
	char	*storage;
	char	*tmp;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		error_open_map();
	tmp = ft_strdup("");
	new_line = get_next_line(fd);
	if (!new_line)
		error_empty_map_file();
	while (new_line)
	{
		storage = ft_strjoin(tmp, new_line);
		free(tmp);
		free(new_line);
		new_line = get_next_line(fd);
		tmp = storage;
	}
	free(new_line);
	split_into_maps(game, storage);
	map_validation(game, storage);
	free_map(game->flood_map);
	free(storage);
}

void	map_init(t_game *game)
{
	int32_t	xy[2];

	game->player_direction = 'R';
	xy[1] = 0;
	while (game->map[xy[1]])
	{
		xy[0] = 0;
		while (game->map[xy[1]][xy[0]])
		{
			if (game->map[xy[1]][xy[0]] == KEY_SPACE)
				put_picture(game->mlx, xy, 1, game->img_space);
			if (game->map[xy[1]][xy[0]] == KEY_WALL)
				put_picture(game->mlx, xy, 1, game->img_wall);
			if (game->map[xy[1]][xy[0]] == KEY_COLL)
				put_picture(game->mlx, xy, 2, game->img_space, game->img_coll);
			if (game->map[xy[1]][xy[0]] == KEY_EXIT)
				put_picture(game->mlx, xy, 2, game->img_space, game->img_exit);
			if (game->map[xy[1]][xy[0]] == KEY_PLAYER)
				put_picture(\
					game->mlx, xy, 2, game->img_space, game->img_player_right);
			xy[0]++;
		}
		xy[1]++;
	}
}

void	create_game_map(t_game *game, t_textures *textures)
{
	load_textures(textures);
	set_window_size(game);
	game->mlx = mlx_init(\
		game->screen_x * PIXEL, game->screen_y * PIXEL, PROGRAM_NAME, false);
	load_images(game, textures);
	map_init(game);
}
