/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:41:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 10:27:38 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coor	int_hor(t_coor point, t_coor origine, double angle)
{
	t_coor	npoint;

	if (point.y < origine.y)
		npoint.y = floor(origine.y / GRID) * GRID;
	else
		npoint.y = floor(origine.y / GRID) * GRID + GRID;
	npoint.x = origine.x + ((origine.y - npoint.y) / tan(angle));
	return (npoint);
}

t_coor	hor_cast(t_data *d, t_coor p, t_coor o, double a)
{
	t_coor	pxa;
	double	xstep;
	double	ystep;

	pxa = int_hor(p, o, a);
	xstep = (double)GRID / tan(a);
	ystep = GRID;
	if (o.x > p.x && xstep > 0)
		xstep *= -1;
	else if (o.x < p.x && xstep < 0)
		xstep *= -1;
	if (o.y > p.y)
		ystep *= -1;
	while (pxa.x >= 0 && pxa.x < d->img2d.width
		&& pxa.y >= 0 && pxa.y < d->img2d.height)
	{
		if (d->map[(int)(pxa.y / GRID)][(int)(pxa.x / GRID)] == '1' ||
			(ystep < 0
			&& d->map[(int)((pxa.y - 1) / GRID)][(int)(pxa.x / GRID)] == '1'))
			break ;
		pxa.y += ystep;
		pxa.x += xstep;
	}
	return (pxa);
}
