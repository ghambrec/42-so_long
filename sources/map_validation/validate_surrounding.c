/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_surrounding.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:44:31 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/11 11:51:11 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_size_y(char **map)
{
	int	c;

	c = 0;
	while (map[c])
		c++;
	return (c);
}

void	validate_surrounding(t_game *game, char *map_string)
{
	int	i;
	int	size_x;
	int	size_y;

	size_x = ft_strlen(game->map[0]);
	size_y = get_size_y(game->map);
	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != '1' || game->map[size_y - 1][i] != '1')
			validate_error("Map is not surrounded by walls!", game, map_string);
		i++;
	}
	i = 1;
	while (i < size_y)
	{
		if (game->map[i][0] != '1' || game->map[i][size_x - 1] != '1')
			validate_error("Map is not surrounded by walls!", game, map_string);
		i++;
	}
}
