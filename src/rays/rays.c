/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:30:40 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/27 18:30:54 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coor  	castARay(t_coor point, t_coor origine, double angle, int *strip_texture)
{
	t_coor		pointXA;
	t_coor		pointYA;
	double		lxa;
	double		lya;

	pointXA = horizontalCast(point, origine, angle);
	pointYA = verticalCast(point, origine, angle);
	lxa = getLengthRay(pointXA, origine, angle);
	lya = getLengthRay(pointYA, origine, angle);
	if (round(lxa) < round(lya))
	{
		*strip_texture = (int)pointXA.x % GRID;
		return (pointXA);
	}
	else 
	{
		*strip_texture = (int)pointYA.y % GRID;
		return (pointYA);
	}
	return (point);
}

t_ray	*castFirstRay(t_ray **rays, t_frame *img, double angle)
{
	t_coor point;
	t_coor origine;
	t_ray *first_ray;

	point = img->triangle.a;
	origine = img->triangle.milieu;
	first_ray = rays[NBRAYS / 2];
	first_ray->coor = castARay(point, origine, angle, &first_ray->posstripwall);
	first_ray->length = getLengthRay(first_ray->coor, origine, angle);
	first_ray->length = correctFishEye(first_ray->length, 0);
	return (first_ray);
}

void	castRigthRays(t_ray **rays, t_ray *first_ray, t_frame *img, double angleinc, double angle)
{
	int			i;
	double		cumulangle;
	t_ray		*rray;
	t_coor		_ray;

	i = 0;
	cumulangle = 0;
	rray = rays[NBRAYS / 2 + 1];
	_ray = first_ray->coor;
	while (i < NBRAYS / 2)
	{
		rrotatePoint(angleinc, &_ray.x, &_ray.y, img->triangle.milieu);
		angle -= angleinc;
		cumulangle += angleinc;
		_ray = castARay(_ray, img->triangle.milieu, angle, &rray->posstripwall);
		rray->length = getLengthRay(_ray, img->triangle.milieu, angle);
		rray->length = correctFishEye(rray->length, cumulangle);
		i++;
		rray->coor.x = _ray.x;
		rray->coor.y = _ray.y;
		rray = rays[NBRAYS / 2 + 1 + i];
	}
}

void	castLeftRays(t_ray **rays, t_ray *first_ray, t_frame *img, double angleinc, double angle)
{
	int			i;
	double		cumulangle;
	t_ray		*lray;
	t_coor		_ray;

	i = 0;
	cumulangle = 0;
	lray = rays[NBRAYS / 2 - 1];
	_ray = first_ray->coor;
	rotatePoint(angleinc, &_ray.x, &_ray.y, img->triangle.milieu);
	angle += angleinc;
	while (i < NBRAYS / 2)
	{
		rotatePoint(angleinc, &_ray.x, &_ray.y, img->triangle.milieu);
		angle += angleinc;
		cumulangle += angleinc;
		_ray = castARay(_ray, img->triangle.milieu, angle, &lray->posstripwall);
		lray->length = getLengthRay(_ray, img->triangle.milieu, angle);
		lray->length = correctFishEye(lray->length, cumulangle);
		i++;
		lray->coor.x = _ray.x;
		lray->coor.y = _ray.y;
		lray = rays[NBRAYS / 2 - 1 - i];
	}
}

t_ray	**castRays(t_frame *img)
{
	double		angle;
	double		angleinc;
	t_coor		origine;
	t_ray		**rays;

	origine = img->triangle.milieu;
	rays = initTabRays();
    angleinc = deg2rad(60 / (double)(LENGTH)); 
	angle = getAnlge(img->triangle.a, origine);

	// first ray triangle.milieu -> triangle.a
	t_ray *first_ray = castFirstRay(rays, img, angle);

	// balayage milieu -> droite
	castRigthRays(rays, first_ray, img, angleinc, angle);
	// balayge milieu -> gauche
	castLeftRays(rays, first_ray, img, angleinc, angle);

	return (rays);
}





