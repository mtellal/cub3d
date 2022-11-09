/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:18:24 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/08 16:49:20 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	addpixelx(t_triangle *t, double pixel)
{
	t->no.x += pixel;
	t->ne.x += pixel;
	t->so.x += pixel;
	t->se.x += pixel;
	t->a.x += pixel;
	t->b.x += pixel;
	t->c.x += pixel;
	t->milieu.x += pixel;
	t->ipos.l += pixel;
}

void	addpixely(t_triangle *t, double pixel)
{
	t->no.y += pixel;
	t->ne.y += pixel;
	t->so.y += pixel;
	t->se.y += pixel;
	t->a.y += pixel;
	t->b.y += pixel;
	t->c.y += pixel;
	t->milieu.y += pixel;
	t->ipos.h += pixel;
}

double	deg2rad(double degrees)
{
	return (degrees * (M_PI / 180));
}

double	rad2deg(double radians)
{
	return (radians * (180 / M_PI));
}

int	check_wall(t_data *d, t_coor ipoint, int inc_x, int inc_y)
{
	int		i;
	t_coor	rpoint;

	i = 0;
	rpoint.x = ipoint.x;
	rpoint.y = ipoint.y;
	while (i < 30)
	{
		if (d->map[(int)((rpoint.y + inc_y) / GRID)]
			[(int)((rpoint.x + inc_x) / GRID)] == '1')
			return (0);
		rotatepoint(deg2rad(i), &rpoint.x, &rpoint.y, d->p.pos);
		i++;
	}
	rpoint.x = ipoint.x;
	rpoint.y = ipoint.y;
	while (i - 30 < 30)
	{
		if (d->map[(int)((rpoint.y + inc_y) / GRID)]
			[(int)((rpoint.x + inc_x) / GRID)] == '1')
			return (0);
		rrotatepoint(deg2rad(i), &rpoint.x, &rpoint.y, d->p.pos);
		i++;
	}
	return (1);
}
