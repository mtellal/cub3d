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

	point = data->img2D.triangle.a;
	origine = data->img2D.triangle.milieu;
	first_ray = rays[(int)(data->img2D.width / 2)];
	first_ray->coor = castaray(data, point, angle, first_ray);
	first_ray->length = getlengthray(first_ray->coor, origine, angle);
	first_ray->length = correctfisheye(first_ray->length, 0);
}

void	c_rrays(t_data *d, t_ray **rays, double angleinc, double angle)
{
	int			i;
	double		cumulangle;
	t_ray		*rr;
	t_coor		cr;

	i = 0;
	cumulangle = 0;
	rr = rays[(int)(d->img2D.width / 2) + 1];
	cr = rays[(int)(d->img2D.width / 2)]->coor;
	while (i < (int)(d->img2D.width / 2))
	{
		rrotatepoint(deg2rad(angleinc), &cr.x, &cr.y, d->img2D.triangle.milieu);
		angle -= angleinc;
		cumulangle += angleinc;
		cr = castaray(d, cr, deg2rad(angle), rr);
		rr->length = getlengthray(cr, d->img2D.triangle.milieu, deg2rad(angle));
		rr->length = correctfisheye(rr->length, deg2rad(cumulangle));
		i++;
		rr->coor.x = cr.x;
		rr->coor.y = cr.y;
		if (d->img2D.width / 2 + 1 + i < d->img2D.width)
			rr = rays[(int)(d->img2D.width / 2) + 1 + i];
	}
}

void	c_frays(t_data *d, t_ray **rays, double angleinc, double angle)
{
	int			i;
	double		cumulangle;
	t_ray		*lr;
	t_coor		cr;

	i = 0;
	cumulangle = 0;
	lr = rays[(int)(d->img2D.width / 2 - 1)];
	cr = rays[(int)(d->img2D.width / 2)]->coor;
	rotatepoint(deg2rad(angleinc), &cr.x, &cr.y, d->img2D.triangle.milieu);
	angle += angleinc;
	while (i < d->img2D.width / 2)
	{
		rotatepoint(deg2rad(angleinc), &cr.x, &cr.y, d->img2D.triangle.milieu);
		angle += angleinc;
		cumulangle += angleinc;
		cr = castaray(d, cr, deg2rad(angle), lr);
		lr->length = getlengthray(cr, d->img2D.triangle.milieu, deg2rad(angle));
		lr->length = correctfisheye(lr->length, deg2rad(cumulangle));
		i++;
		lr->coor.x = cr.x;
		lr->coor.y = cr.y;
		if (d->img2D.width / 2 - 1 - i >= 0)
			lr = rays[d->img2D.width / 2 - 1 - i];
	}
}

t_ray	**castrays(t_data *data)
{
	double		angle;
	double		angleinc;
	t_coor		origine;
	t_ray		**rays;

	origine = data->img2D.triangle.milieu;
	rays = inittabrays(data->img2D.width);
	angleinc = 60 / (double)(data->img2D.width);
	angle = rad2deg(getanlge(data->img2D.triangle.a, origine));
	castfirstray(data, rays, deg2rad(angle));
	c_rrays(data, rays, angleinc, angle);
	c_frays(data, rays, angleinc, angle);
	return (rays);
}
