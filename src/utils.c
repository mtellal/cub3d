/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:34:06 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 14:46:40 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	displaycoor(t_coor point)
{
	ft_putstr_fd("coor point x/y\n", 1);
	ft_putstr_fd("x = ", 1);
	ft_putnbr_fd(point.x, 1);
	ft_putstr_fd(" y = ", 1);
	ft_putnbr_fd(point.y, 1);
	ft_putstr_fd("\n\n", 1);
}

double	abs_value(double value)
{
	if (value < 0)
		return (-value);
	return (value);
}

void	quit_err_msg(char *s)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}