/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_characters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:20:27 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/10 13:23:58 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_characters(char *map_string, char character)
{
	int counter;
	
	counter = 0;
	while (*map_string)
	{
		if (*map_string == character)
			counter++;
		map_string++;
	}
	return (counter);
}

void	validate_characters(char **map, char *map_string)
{
	int		num_player;
	int		num_exit;
	int		num_coll;
	char	*cpy;
	
	num_player = count_characters(map_string, KEY_PLAYER);
	if (num_player != 1)
		validate_error("Map needs exactly 1 Player to be valid!", map, map_string);
	num_exit = count_characters(map_string, KEY_EXIT);
	if (num_exit != 1)
		validate_error("Map needs exactly 1 Exit to be valid!", map, map_string);
	num_coll = count_collectibles(map);
	if (num_coll == 0)
		validate_error("No collectibles!", map, map_string);
	cpy = map_string;
	while (*cpy)
	{
		if (*cpy != KEY_COLL && *cpy != KEY_EXIT && *cpy != KEY_PLAYER && *cpy != KEY_SPACE && *cpy != KEY_WALL && *cpy != '\n')
			validate_error("Invalid character in map file!", map, map_string);
		cpy++;
	}
}
