/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:30:40 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 11:43:25 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	castfirstray(t_data *data, t_ray **rays, double angle)
{
	t_coor	point;
	t_coor	origine;
	t_ray	*first_ray;

	point = data->p.up;
	origine = data->p.pos;
	first_ray = rays[(int)(data->img3d.width / 2)];
	first_ray->coor = castaray(data, point, angle, first_ray);
	first_ray->length = getlengthray(first_ray->coor, origine, angle);
	first_ray->length = correctfisheye(first_ray->length, 0);
}

void	uniformize_rays(t_ray *rr, t_ray *ri)
{
	if ((int)rr->coor.x == (int)ri->coor.x
		&& (int)rr->coor.y == (int)ri->coor.y
		&& (int)rr->length != (int)ri->length)
		ri->length = rr->length;
}

void	c_rrays(t_data *d, t_ray **rays, double angleinc, double angle)
{
	int			i;
	double		cumulangle;
	t_ray		*rr;
	t_coor		cr;

	i = 0;
	cumulangle = 0;
	rr = rays[(int)(d->img3d.width / 2) + 1];
	cr = rays[(int)(d->img3d.width / 2)]->coor;
	while (i < d->img3d.width / 2)
	{
		rrotatepoint(deg2rad(angleinc), &cr.x, &cr.y, d->p.pos);
		angle -= angleinc;
		cumulangle += angleinc;
		cr = castaray(d, cr, deg2rad(angle), rr);
		rr->length = getlengthray(cr, d->p.pos, deg2rad(angle));
		rr->length = correctfisheye(rr->length, deg2rad(cumulangle));
		rr->coor.x = cr.x;
		rr->coor.y = cr.y;
		uniformize_rays(rr, rays[(int)(d->img3d.width / 2) + i]);
		i++;
		if (d->img3d.width / 2 + 1 + i < d->img3d.width)
			rr = rays[(int)(d->img3d.width / 2) + 1 + i];
	}
}

void	c_lrays(t_data *d, t_ray **rays, double angleinc, double angle)
{
	int			i;
	double		cumulangle;
	t_ray		*lr;
	t_coor		cr;

	i = 0;
	cumulangle = 0;
	lr = rays[(int)(d->img3d.width / 2 - 1)];
	cr = rays[(int)(d->img3d.width / 2)]->coor;
	rotatepoint(deg2rad(angleinc), &cr.x, &cr.y, d->p.pos);
	angle += angleinc;
	while (i < d->img3d.width / 2)
	{
		rotatepoint(deg2rad(angleinc), &cr.x, &cr.y, d->p.pos);
		angle += angleinc;
		cumulangle += angleinc;
		cr = castaray(d, cr, deg2rad(angle), lr);
		lr->length = getlengthray(cr, d->p.pos, deg2rad(angle));
		lr->length = correctfisheye(lr->length, deg2rad(cumulangle));
		lr->coor.x = cr.x;
		lr->coor.y = cr.y;
		uniformize_rays(lr, rays[(int)(d->img3d.width / 2) - i++]);
		if (d->img3d.width / 2 - 1 - i >= 0)
			lr = rays[d->img3d.width / 2 - 1 - i];
	}
}

t_ray	**castrays(t_data *data)
{
	double		angle;
	double		angleinc;
	t_coor		origine;
	t_ray		**rays;

	origine = data->p.pos;
	rays = inittabrays(data->img3d.width);
	angleinc = 60 / (double)(data->img3d.width);
	angle = rad2deg(getanlge(data->p.up, origine));
	castfirstray(data, rays, deg2rad(angle));
	c_rrays(data, rays, angleinc, angle);
	c_lrays(data, rays, angleinc, angle);
	return (rays);
}
