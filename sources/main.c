/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:57:55 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/11 12:48:18 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	leaks(void)
// {
// 	system("leaks so_long");
// }

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
	mlx_terminate(game.mlx);
	free_map(game.map);
	return (EXIT_SUCCESS);
}
