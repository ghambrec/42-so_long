/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:36:45 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/10 12:50:16 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int pos;

	if (!map)
		return ;
	pos = 0;
	while (map[pos])
	{
		free(map[pos]);
		map[pos] = NULL;
		pos++;
	}
	free(map);
}

int	count_collectibles(char **map)
{
	int32_t x;
	int32_t y;
	int		number_coll;

	number_coll = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == KEY_COLL)
				number_coll++;
			x++;
		}
		y++;
	}
	return (number_coll);
}
