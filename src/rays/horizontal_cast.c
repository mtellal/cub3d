/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:41:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/16 11:41:55 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coor	firstIntersectionHorizontal(t_coor point, t_coor origine, double angle)
{

	t_coor npoint;
	(void)angle;

	//face up / down
	if (point.y < origine.y)
		npoint.y = floor(origine.y / GRID) * GRID;
	else
		npoint.y = floor(origine.y / GRID) * GRID + GRID;
	npoint.x = origine.x + ((origine.y - npoint.y) / tan(angle));
	return (npoint);
}

t_coor	horizontalCast(t_data *data, t_coor point, t_coor origine, double angle)
{
	t_coor pointXA = firstIntersectionHorizontal(point, origine, angle);

	double xstep = (double)GRID / tan(angle);
	double ystep = GRID;

	// facing right
	if (origine.x > point.x && xstep > 0)
		xstep *= -1;
	// facing left
	else if (origine.x < point.x && xstep < 0)
		xstep *= -1;

	// facing down
	if (origine.y > point.y)
		ystep *= -1;

	while (pointXA.x >= 0 && pointXA.x < data->img2D.width &&
			pointXA.y >= 0 && pointXA.y < data->img2D.height)
	{
		if (data->map[(int)(pointXA.y / GRID)][(int)(pointXA.x / GRID)] == '1' ||
			(ystep < 0 && data->map[(int)((pointXA.y - 1) / GRID)][(int)(pointXA.x / GRID)] == '1'))
		{
			break ;
		}
			pointXA.y += ystep;
			pointXA.x += xstep;
	}

	return (pointXA);
}