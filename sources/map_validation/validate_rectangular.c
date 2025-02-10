/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rectangular.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:26:53 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/10 13:43:13 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_rectangular(char **map, char *map_string)
{
	size_t	init_x;
	int	i;

	init_x = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) != init_x)
			validate_error("Map not rectangular!", map, map_string);
		i++;
	}
}
