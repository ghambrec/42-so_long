/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:38:53 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/05 15:39:26 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// // noch testen!!
void	perror_exit_mlx(char *error)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	// ft_putendl_fd(mlx_strerror(mlx_errno),STDERR_FILENO);
	exit(mlx_errno);
}

// fuer mapval noch perror_exit ?