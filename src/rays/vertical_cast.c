/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_cast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:46:26 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 10:41:15 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coor	int_vert(t_coor point, t_coor origine, double angle)
{
	t_coor	npoint;

	if (point.x > origine.x)
		npoint.x = floor(origine.x / GRID) * GRID + GRID;
	else
		npoint.x = floor(origine.x / GRID) * GRID;
	npoint.y = origine.y - (npoint.x - origine.x) * tan(angle);
	return (npoint);
}

t_coor	vert_cast(t_data *d, t_coor p, t_coor o, double a)
{
	double	xstep;
	double	ystep;
	t_coor	pya;

	pya = int_vert(p, o, a);
	ystep = (double)GRID * tan(a);
	xstep = GRID;
	if (p.x < o.x)
		xstep *= -1;
	if (p.y < o.y && ystep > 0)
		ystep *= -1;
	if (p.y > o.y && ystep < 0)
		ystep *= -1;
	while (pya.x >= 0 && pya.x < d->img2D.width
		&& pya.y >= 0 && pya.y < d->img2D.height)
	{
		if (d->map[(int)(pya.y / GRID)][(int)(pya.x / GRID)] == '1'
			|| (xstep < 0
			&& d->map[(int)(pya.y / GRID)][(int)((pya.x - 1) / GRID)] == '1'))
			break ;
		pya.y += ystep;
		pya.x += xstep;
	}
	return (pya);
}
