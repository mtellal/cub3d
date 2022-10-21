/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:04:06 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/21 16:27:45 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	rotatex(double angle, double x, double y, int r)
{
	if (r)
		return (x * -cos(angle) + y * sin(angle));
	return (x * cos(angle) + y * -sin(angle));
}

double	rotatey(double angle, double x, double y, int r)
{
	if (r)
		return (x * -sin(angle) + y * -cos(angle));
	return ((x * sin(angle) + y * cos(angle)));
}

void	rotatepoint(double angle, double *x, double *y, t_coor origine)
{
	double	opos_x;
	double	opos_y;

	opos_x = *x - origine.x;
	opos_y = origine.y - *y;
	*x = rotatex(angle, opos_x, opos_y, 0);
	*x += origine.x;
	*y = rotatey(angle, opos_x, opos_y, 0);
	*y = origine.y - *y;
}

void	rrotatepoint(double angle, double *x, double *y, t_coor origine)
{
	double	opos_x;
	double	opos_y;

	opos_x = origine.x - *x;
	opos_y = origine.y - *y;
	*x = rotatex(angle, opos_x, opos_y, 1);
	*x += origine.x;
	*y = rotatey(angle, opos_x, opos_y, 1);
	*y += origine.y;
}
