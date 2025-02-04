/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:57:55 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/04 14:40:33 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_argument(int argc, char *map_name)
{
	char	*map_suffix;

	map_suffix = ".ber";
	if (argc != 2)
	{
		ft_putendl_fd("Error\nInvalid number of arguments", STDERR_FILENO);
		exit(1);
	}
	if (ft_strlen(map_name) <= 4)
	{
		ft_putendl_fd("Error\nInvalid map name", STDERR_FILENO);
		exit(1);
	}
	if (ft_strncmp(map_name + ft_strlen(map_name) - 4, map_suffix, 4) != 0)
	{
		ft_putendl_fd("Error\nInvalid map name", STDERR_FILENO);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	check_argument(argc, argv[1]);

	return (EXIT_SUCCESS);
}