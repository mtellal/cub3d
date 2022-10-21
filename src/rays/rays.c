/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:30:40 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/20 13:31:12 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coor  	castARay(t_data *data, t_coor point, t_coor origine, double angle, int *strip_texture, int *walldirection)
{
	t_coor		pointXA;
	t_coor		pointYA;
	double		lxa;
	double		lya;

	pointXA = horizontalCast(data, point, origine, angle);
	pointYA = verticalCast(data, point, origine, angle);
	lxa = getLengthRay(pointXA, origine, angle);
	lya = getLengthRay(pointYA, origine, angle);

	if (lxa < lya)
	{
		if (pointXA.y < origine.y)
			*walldirection = NORD;
		else
			*walldirection = SUD;
		*strip_texture = (int)pointXA.x % GRID;
		return (pointXA);
	}
	else
	{
		if (pointYA.x < origine.x)
			*walldirection = OUEST;
		else
			*walldirection = EST;
		*strip_texture = (int)pointYA.y % GRID;
		return (pointYA);
	}
	return (point);
}

t_ray	*castFirstRay(t_data *data, t_ray **rays, double angle)
{
	t_coor point;
	t_coor origine;
	t_ray *first_ray;

	point = data->img2D.triangle.a;
	origine = data->img2D.triangle.milieu;
	first_ray = rays[(int)(data->img2D.width / 2)];
	first_ray->coor = castARay(data, point, origine, angle, &first_ray->posstripwall, &first_ray->walldirection);
	first_ray->length = getLengthRay(first_ray->coor, origine, angle);
	first_ray->length = correctFishEye(first_ray->length, 0);
	return (first_ray);
}

void	castRigthRays(t_data *data, t_ray **rays, t_ray *first_ray, double angleinc, double angle)
{
	int			i;
	double		cumulangle;
	t_ray		*rray;
	t_coor		_ray;

	(void)data;
	(void)rays;
	(void)first_ray;
	(void)angleinc;
	(void)angle;

	(void)i;
	(void)cumulangle;
	(void)rray;
	(void)_ray;

	i = 0;
	cumulangle = 0;
	rray = rays[(int)(data->img2D.width / 2) + 1];
	_ray = first_ray->coor;
	while (i < (int)(data->img2D.width / 2))
	{
		rrotatePoint(deg2rad(angleinc), &_ray.x, &_ray.y, data->img2D.triangle.milieu);
		angle -= angleinc;
		cumulangle += angleinc;
		_ray = castARay(data, _ray, data->img2D.triangle.milieu, deg2rad(angle), &rray->posstripwall, &rray->walldirection);
		rray->length = getLengthRay(_ray, data->img2D.triangle.milieu, deg2rad(angle));
		rray->length = correctFishEye(rray->length, deg2rad(cumulangle));
		i++;
		rray->coor.x = _ray.x;
		rray->coor.y = _ray.y;
		if (data->img2D.width / 2 + 1 + i < data->img2D.width)
			rray = rays[(int)(data->img2D.width / 2) + 1 + i];
	}
}

void	castLeftRays(t_data *data, t_ray **rays, t_ray *first_ray, double angleinc, double angle)
{
	int			i;
	double		cumulangle;
	t_ray		*lray;
	t_coor		_ray;

	i = 0;
	cumulangle = 0;
	lray = rays[data->img2D.width / 2 - 1];
	_ray = first_ray->coor;
	rotatePoint(deg2rad(angleinc), &_ray.x, &_ray.y, data->img2D.triangle.milieu);
	angle += angleinc;
	while (i < data->img2D.width / 2)
	{
		rotatePoint(deg2rad(angleinc), &_ray.x, &_ray.y, data->img2D.triangle.milieu);
		angle += angleinc;
		cumulangle += angleinc;
		_ray = castARay(data, _ray, data->img2D.triangle.milieu, deg2rad(angle), &lray->posstripwall, &lray->walldirection);
		lray->length = getLengthRay(_ray, data->img2D.triangle.milieu, deg2rad(angle));
		lray->length = correctFishEye(lray->length, deg2rad(cumulangle));
		i++;
		lray->coor.x = _ray.x;
		lray->coor.y = _ray.y;
		if (data->img2D.width / 2 - 1 - i >= 0)
			lray = rays[data->img2D.width / 2 - 1 - i];
	}
}

t_ray	**castRays(t_data *data)
{
	double		angle;
	double		angleinc;
	t_coor		origine;
	t_ray		**rays;

	origine = data->img2D.triangle.milieu;
	rays = initTabRays(data->img2D.width);
    angleinc = 60 / (double)(data->img2D.width); 
	angle = rad2deg(getAnlge(data->img2D.triangle.a, origine));

	t_ray *first_ray = castFirstRay(data, rays, deg2rad(angle));

	(void)first_ray;
	castRigthRays(data, rays, first_ray, angleinc, angle);
	castLeftRays(data, rays, first_ray, angleinc, angle);

	return (rays);
}





