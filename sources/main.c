/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:57:55 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/11 13:07:30 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_game(t_game *game)
{
	if (game->img_coll)
		mlx_delete_image(game->mlx, game->img_coll);
	if (game->img_exit)
		mlx_delete_image(game->mlx, game->img_exit);
	if (game->img_exit_finished)
		mlx_delete_image(game->mlx, game->img_exit_finished);
	if (game->img_player_left)
		mlx_delete_image(game->mlx, game->img_player_left);
	if (game->img_player_right)
		mlx_delete_image(game->mlx, game->img_player_right);
	if (game->img_space)
		mlx_delete_image(game->mlx, game->img_space);
	if (game->img_wall)
		mlx_delete_image(game->mlx, game->img_wall);
	if (game->img_win)
		mlx_delete_image(game->mlx, game->img_win);
	free_map(game->map);
	mlx_terminate(game->mlx);
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

// void	leaks(void)
// {
// 	system("leaks so_long");
// }

	// atexit(leaks);
int	main(int argc, char **argv)
{
	t_game		game;
	t_textures	textures;

	check_argument(argc, argv[1]);
	get_map(argv[1], &game);
	create_game_map(&game, &textures);
	mlx_key_hook(game.mlx, keyhook, &game);
	mlx_loop(game.mlx);
	clean_game(&game);
	return (EXIT_SUCCESS);
}
