/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayRays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:37:13 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 09:30:40 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*wallimg(t_texture *t, t_ray *r)
{
	if (r->walldirection == NORD)
		return (&t->walln);
	else if (r->walldirection == SUD)
		return (&t->walls);
	else if (r->walldirection == OUEST)
		return (&t->wallo);
	else if (r->walldirection == EST)
		return (&t->walle);
	return (NULL);
}

void	calculstripwall(t_data *d, t_ray *r, t_drays *drays)
{
	double		scale_y;
	t_img		*twall;

	twall = wallimg(&d->texture, r);
	drays->piw.y = 0;
	drays->piw.x = r->posstripwall * twall->width / (double)(GRID);
	scale_y = (double)(twall->height) / drays->w.h;
	if (drays->pw.y < 0)
		drays->pw.y = 0;
	if (drays->w.h >= (double)(d->img3d.height))
	{
		drays->piw.y = (drays->w.h - (double)d->img3d.height) / 2 * scale_y;
		drays->w.h = d->img3d.height;
	}
	dissw(&d->img3d, twall, drays, scale_y);
}

void	displayimg3d(t_data *d, t_ray *r, t_drays *drays)
{
	t_texture	*t;
	t_frame		*i;

	t = &d->texture;
	i = &d->img3d;
	dis_c(i, t->cieling, drays->pw, drays->w.l);
	calculstripwall(d, r, drays);
	drays->pw.y += drays->w.h;
	dis_f(i, t->floor, drays->pw, drays->w.l);
}

void	displayrays(t_data *d, t_ray **rays)
{
	int			i;
	double		distpp;
	t_ray		*_ray;
	t_drays		drays;

	i = 0;
	distpp = ((double)d->img3d.height / 2) / tan(deg2rad(30));
	drays.w.l = (double)(d->img3d.width) / (double)(d->img2d.width);
	while (i < d->img2d.width)
	{
		_ray = rays[i];
		if (_ray)
		{
			drays.w.h = ((double)GRID / _ray->length) * distpp;
			drays.pw.x = drays.w.l * i;
			drays.pw.y = ((double)d->img3d.height / 2) - (drays.w.h / 2);
			displayimg3d(d, _ray, &drays);
		}
		i++;
	}
}
