/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_cast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:46:26 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/16 11:46:33 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coor	firstIntersectionVertical(t_coor point, t_coor origine, double angle)
{
	t_coor npoint;

	// facing right / left
	if (point.x > origine.x)
		npoint.x = floor(origine.x / GRID) * GRID + GRID;
	else
		npoint.x = floor(origine.x / GRID) * GRID;

	npoint.y = origine.y - (npoint.x - origine.x) * tan(angle);
	return (npoint);
}

t_coor	verticalCast(t_data *data, t_coor point, t_coor origine, double angle)
{
	t_coor pointYA = firstIntersectionVertical(point, origine, angle);

	double ystep = (double)GRID * tan(angle);
	double xstep = GRID;

	//facing left
	if (point.x < origine.x)
		xstep *= -1;

	// facing up
	if (point.y < origine.y && ystep > 0)
		ystep *= -1;
	// facing down
	if (point.y > origine.y && ystep < 0)
		ystep *= -1;

	while (pointYA.x >= 0 && pointYA.x < data->img2D.width &&
			pointYA.y >= 0 && pointYA.y < data->img2D.height)
	{
		if (data->map[(int)(pointYA.y / GRID)][(int)(pointYA.x / GRID)] == '1' || 
			(xstep < 0 && data->map[(int)(pointYA.y / GRID)][(int)((pointYA.x - 1) / GRID)] == '1'))
			break ;
		pointYA.y += ystep;
		pointYA.x += xstep;
	}

	return (pointYA);
}