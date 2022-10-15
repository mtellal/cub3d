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

/*

	SEE DOCS	http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
				https://permadi.com/1996/05/ray-casting-tutorial-7/

*/


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

/////////////////////////////////////////////////////////////////////////////////////////


t_coor	horizontalCast(t_coor point, t_coor origine, double angle)
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

	while (pointXA.x >= 0 && pointXA.x < LENGTH &&
			pointXA.y >= 0 && pointXA.y < HEIGHT)
	{
		if (map[(int)(pointXA.y / GRID)][(int)(pointXA.x / GRID)] == '1' ||
			(ystep < 0 && map[(int)((pointXA.y - 1) / GRID)][(int)(pointXA.x / GRID)] == '1'))
		{
			break ;
		}
			pointXA.y += ystep;
			pointXA.x += xstep;
	}

	return (pointXA);
}

t_coor	verticalCast(t_coor point, t_coor origine, double angle)
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

	while (pointYA.x >= 0 && pointYA.x < LENGTH &&
			pointYA.y >= 0 && pointYA.y < HEIGHT)
	{
		if (map[(int)(pointYA.y / GRID)][(int)(pointYA.x / GRID)] == '1' || 
			(xstep < 0 && map[(int)(pointYA.y / GRID)][(int)((pointYA.x - 1) / GRID)] == '1'))
			break ;
		pointYA.y += ystep;
		pointYA.x += xstep;
	}

	return (pointYA);
}

/*	selon un point (ex ray.b (qui est une rotation de img.a)) et une origine (ex milieu trinagle)
 *	prolonge la droite point origine, jusqu'a atteindre un mur
 *	verifie la detection de mur avec xa et ya (detection horizontal et vertical)
 *	renvoie les coor juste avant le mur
*/

t_coor  	ray(t_coor point, t_coor origine, double angle, int *strip_texture)
{
	t_coor pointXA = horizontalCast(point, origine, angle);
	t_coor pointYA = verticalCast(point, origine, angle);

	double lxa;
	double lya;

	lxa = getLengthRay(pointXA, origine, angle);
	lya = getLengthRay(pointYA, origine, angle);

	/* displayCoor(pointXA);
	displayCoor(pointYA);
	displayCoor(origine); */
	/* ft_putnbr_fd(lxa, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(lya, 1);
	ft_putstr_fd("\n", 1); */

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


//	pour corriger le fish eye d'un rayon, il faut multiplier sa longueur par le cos d'un angle
//	angle du milieu du fov (+/-90deg ou direction du personnage) et le point ou le rayon a touche le mur 

double	correctFishEye(double length, double cumulangle)
{

	return (length * cos(cumulangle));
}


void	castRays(t_data *data, t_frame *img, t_frame *img2, t_coor origine, double nbrays, int color, int color2)
{
	int			i;
	double		current_angle;
	double		angle;
	double		angleinc;
	double		cumulangle;

	(void) img2;
	(void)nbrays;
	(void)origine;
	(void)color2;
	(void)data;
	(void)current_angle;
	(void)angle;
	(void)angleinc;
	(void)cumulangle;
	(void)i;
	(void)color;

	i = 0;

	current_angle = 60;

    angleinc = deg2rad(current_angle / (double)(LENGTH)); 

	// angle place a haut droit du triangle (60deg depuis (x,y)(1,0)) comment dans un repere classique
	angle = getAnlge(img->triangle.a, origine);

	cumulangle = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// la bande ou le rayon a ete touche sur le mur rayon % GRID(check ray())
	int poslwall;

	double plength = 0;
	double length = 0;

	(void)plength;
	(void)poslwall;
	(void)length;

/////////////////////////////////////////////////////////////////////////////////////////////////////

	// CASTING FIRST RAY 
	// ray au milieu, prolongation de img->triangle.a
	t_coor first_ray;

	first_ray = ray(img->triangle.a, origine, angle, &poslwall);

	length = getLengthRay(first_ray, origine, angle);

	put_pixel(img, first_ray.y, first_ray.x, color);

	length = correctFishEye(length, cumulangle);

	displayRays(img2, length, nbrays, color2, 0, &data->texture, poslwall);


////// balayage milieu -> droite
	t_coor rray;

	rray.x = first_ray.x;
	rray.y = first_ray.y;

	i = 0;

	while (i < nbrays / 2 - 1)
	{
		rrotatePoint(angleinc, &rray.x, &rray.y, img->triangle.milieu);
		angle -= angleinc;
		cumulangle += angleinc;

		rray = ray(rray, origine, angle, &poslwall);
		put_pixel(img, rray.y, rray.x, color);
		length = getLengthRay(rray, origine, angle);

		length = correctFishEye(length, cumulangle);
		displayRays(img2, length, nbrays, color2, i, &data->texture, poslwall);
		i++;
	}

	angle = getAnlge(img->triangle.a, origine);
	cumulangle = 0;

	i = 0;

	t_coor lray;

	lray.x = first_ray.x;
	lray.y = first_ray.y;

	rotatePoint(angleinc, &lray.x, &lray.y, img->triangle.milieu);

	angle += angleinc;

	while (i < nbrays / 2)
	{
		rotatePoint(angleinc, &lray.x, &lray.y, img->triangle.milieu);
		angle += angleinc;
		cumulangle += angleinc;

		lray = ray(lray, origine, angle, &poslwall);
		put_pixel(img, lray.y, lray.x, color);
		length = getLengthRay(lray, origine, angle);

		length = correctFishEye(length, cumulangle);
		displayRays(img2, length, nbrays, color2, -i, &data->texture, poslwall);
		i++;
	}


}



