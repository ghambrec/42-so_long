/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:57:55 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/04 19:23:33 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// // noch testen!!
void	perror_exit_mlx_gha(char *error)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	// ft_putendl_fd(mlx_strerror(mlx_errno),STDERR_FILENO);
	exit(mlx_errno);
}

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
	if (!game->map)
	{
		ft_putendl_fd("Error\nSplit failed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	free(storage);
}

void	get_window_size(t_game *game)
{
	int	i;

	game->horizontal = ft_strlen(game->map[0]);
	i = 0;
	while (game->map[i] != NULL && game->map[i][0] == '1')
	{
		i++;
	}
	game->vertical = i;
}

void	load_textures(t_textures *textures)
{
	textures->space = mlx_load_png(PNG_SPACE);
	if (!textures->space)
		perror_exit_mlx_gha("Could not load space png");
}

void	load_images(t_game *game, t_img *img, t_textures *textures)
{
	img->space = mlx_texture_to_image(game->mlx, textures->space);
	if (!img->space)
		perror_exit_mlx_gha("Failed to load space texture into image");
}

void	fill_map(t_game *game, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0')
				mlx_image_to_window(game->mlx, img->space, j * PIXEL, i * PIXEL);
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, img->wall, j * PIXEL, i * PIXEL);
			if (game->map[i][j] == 'C')
				mlx_image_to_window(game->mlx, img->collectible, j * PIXEL, i * PIXEL);
			if (game->map[i][j] == 'E')
				mlx_image_to_window(game->mlx, img->exit, j * PIXEL, i * PIXEL);
			if (game->map[i][j] == 'P')
				mlx_image_to_window(game->mlx, img->player, j * PIXEL, i * PIXEL);
			j++;
		}
		i++;
	}
}

void	create_window(t_game *game, t_textures *textures, t_img *img)
{
	get_window_size(game);
	game->mlx = mlx_init(game->horizontal * PIXEL, game->vertical * PIXEL, PROGRAM_NAME, false);
	load_images(game, img, textures);
	fill_map(game, img);
	
	
	
	
	mlx_loop(game->mlx);
	
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_textures	textures;
	t_img		img;
	
	check_argument(argc, argv[1]);
	get_map(argv[1], &game);
	// validate map hier einbauen!
	load_textures(&textures);
	create_window(&game, &textures, &img);
	
	
	// init_game_map(&game, &img);

	return (EXIT_SUCCESS);
}
