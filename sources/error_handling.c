/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:38:53 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/11 11:41:06 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	perror_exit_mlx(char *error_msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_cc_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
	exit(mlx_errno);
}

void	validate_error(char *error_msg, t_game *game, char *map_string)
{
	free(map_string);
	free_map(game->map);
	free_map(game->flood_map);
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
