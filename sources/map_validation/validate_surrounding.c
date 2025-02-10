/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_surrounding.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:44:31 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/10 14:02:37 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_size_y(char **map)
{
	int c;

	c = 0;
	while (map[c])
		c++;
	return (c);
}

void	validate_surrounding(char **map, char *map_string)
{
	int	i;
	int	size_x;
	int	size_y;

	size_x = ft_strlen(map[0]);
	size_y = get_size_y(map);

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' || map[size_y - 1][i] != '1')
			validate_error("Map is not surrounded by walls!", map, map_string);
		i++;
	}
	i = 1;
	while (i < size_y)
	{
		if (map[i][0] != '1' || map[i][size_x - 1] != '1')
			validate_error("Map is not surrounded by walls!", map, map_string);
		i++;
	}
}
