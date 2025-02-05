/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:57:55 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/05 15:15:05 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// // noch testen!!
void	perror_exit_mlx(char *error)
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

	game->screen_x = ft_strlen(game->map[0]);
	i = 0;
	while (game->map[i] != NULL && game->map[i][0] == '1')
	{
		i++;
	}
	game->screen_y = i;
}

// error check nach jedem notwendig oder am ende nur einmal auf errno pruefen? was ist goto?
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
	textures->player = mlx_load_png(PNG_PLAYER_RIGHT);
	if (!textures->player)
		perror_exit_mlx("Could not load player");
}

void	load_images(t_game *game, t_textures *textures)
{
	game->img_space = mlx_texture_to_image(game->mlx, textures->space);
	if (!game->img_space)
		perror_exit_mlx("Failed to load space texture into image");
	game->img_wall = mlx_texture_to_image(game->mlx, textures->wall);
	if (!game->img_wall)
		perror_exit_mlx("Failed to load wall texture into image");
	game->img_coll = mlx_texture_to_image(game->mlx, textures->coll);
	if (!game->img_coll)
		perror_exit_mlx("Failed to load collectible texture into image");
	game->img_exit = mlx_texture_to_image(game->mlx, textures->exit);
	if (!game->img_exit)
		perror_exit_mlx("Failed to load exit texture into image");
	game->img_exit_finished = mlx_texture_to_image(game->mlx, textures->exit_finished);
	if (!game->img_exit_finished)
		perror_exit_mlx("Failed to load exit_finished texture into image");
	game->img_player = mlx_texture_to_image(game->mlx, textures->player);
	if (!game->img_player)
		perror_exit_mlx("Failed to load player texture into image");
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

void set_player_coords(t_game *game, int32_t xy[2])
{
	game->player_xy[0] = xy[0];
	game->player_xy[1] = xy[1];
}

int	count_collectibles(t_game *game)
{
	int32_t x;
	int32_t y;
	int		number_coll;

	number_coll = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == KEY_COLL)
				number_coll++;
			x++;
		}
		y++;
	}
	return (number_coll);
}

void	map_init(t_game *game)
{
	int32_t	xy[2];

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
			{
				set_player_coords(game, xy);
				put_picture(game->mlx, xy, 2, game->img_space, game->img_player);
			}
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

void	walk(t_game *game, int32_t x, int32_t y)
{
	int32_t new_player_xy[2];

	new_player_xy[0] = game->player_xy[0] + x;
	new_player_xy[1] = game->player_xy[1] + y;
	if (game->map[new_player_xy[1]][new_player_xy[0]] == KEY_EXIT && count_collectibles(game) == 0)
	{
		put_picture(game->mlx, game->player_xy, 1, game->img_space);
		ft_memcpy(game->player_xy, new_player_xy, sizeof(new_player_xy));
		put_picture(game->mlx, game->player_xy, 2, game->img_space, game->img_exit_finished);
		return ;
	}
	if (game->map[game->player_xy[1]][game->player_xy[0]] == KEY_EXIT)
		return ;
	if (game->map[new_player_xy[1]][new_player_xy[0]] == KEY_WALL || game->map[new_player_xy[1]][new_player_xy[0]] == KEY_EXIT)
		return ;
	game->map[new_player_xy[1]][new_player_xy[0]] = KEY_SPACE; //feld auf space setzen
	put_picture(game->mlx, game->player_xy, 1, game->img_space); //vorheriges feld auf space setzen
	ft_memcpy(game->player_xy, new_player_xy, sizeof(new_player_xy)); //player pos aktualisieren
	put_picture(game->mlx, game->player_xy, 1, game->img_player); //player auf neues feld drucken
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
		walk(game, 0, -1);
	if (keydata.key == MLX_KEY_A)
		walk(game, -1, 0);
	if (keydata.key == MLX_KEY_S)
		walk(game, 0, 1);
	if (keydata.key == MLX_KEY_D)
		walk(game, 1, 0);
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
	return (EXIT_SUCCESS);
}
