/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:15:54 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/10 17:28:34 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_validation(t_game *game, char *map_string)
{
	set_player_coords(game);
	validate_characters(game->map, map_string);
	validate_rectangular(game->map, map_string);
	validate_surrounding(game->map, map_string);
	// validate_path(game->map_flood, map_string);
}
