/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:15:54 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/10 14:27:27 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_validation(char **map, char *map_string)
{
	validate_characters(map, map_string);
	validate_rectangular(map, map_string);
	validate_surrounding(map, map_string);
	validate_path(map, map_string);
}
