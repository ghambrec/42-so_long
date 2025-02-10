/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:57:55 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/10 18:40:37 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_argument(int argc, char *map_name)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error\nInvalid number of arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(map_name) <= 4)
	{
		ft_putendl_fd("Error\nInvalid map name", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(map_name + ft_strlen(map_name) - 4, ".ber", 4) != 0)
	{
		ft_putendl_fd("Error\nInvalid map name", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	get_map(char *map_name, t_game *game)
{
	int		fd;
	char	*new_line;
	char	*storage;
	char	*tmp;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nError open map file");
		exit(errno);
	}
	tmp = ft_strdup("");
	new_line = get_next_line(fd);
	while (new_line)
	{
		storage = ft_strjoin(tmp, new_line);
		free(tmp);
		free(new_line);
		new_line = get_next_line(fd);
		tmp = storage;
	}
	free(new_line);
	game->map = ft_split(storage, '\n');
	game->flood_map = ft_split(storage, '\n');
	if (!game->map)
	{
		free(storage);
		ft_putendl_fd("Error\nSplit failed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	map_validation(game, storage);
	free(storage);
}

void	get_window_size(t_game *game)
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
				put_picture(game->mlx, xy, 2, game->img_space, game->img_player_right);
			xy[0]++;
		}
		xy[1]++;
	}
}

void	create_game_map(t_game *game, t_textures *textures)
{
	load_textures(textures);
	get_window_size(game);
	game->mlx = mlx_init(game->screen_x * PIXEL, game->screen_y * PIXEL, PROGRAM_NAME, false);
	load_images(game, textures);
	map_init(game);
}



int	main(int argc, char **argv)
{
	t_game		game;
	t_textures	textures;
	// t_img		img;
	
	check_argument(argc, argv[1]);
	get_map(argv[1], &game);
	// validate map hier einbauen!
	create_game_map(&game, &textures);
	mlx_key_hook(game.mlx, keyhook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map(game.map);
	return (EXIT_SUCCESS);
}
