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

	if (origine.x - point.x >= 0)
		npoint.x = (int)(origine.x / GRID) * GRID - 1;
	else
		npoint.x = (int)(origine.x / GRID) * GRID + GRID;

	npoint.y = origine.y - (origine.x - npoint.x) * tan(angle);
	return (npoint);
}

t_coor	firstIntersectionHorizontal(t_coor point, t_coor origine, double angle)
{
	t_coor npoint;
	(void)angle;

	if (origine.y - point.y >= 0)
		npoint.y = (int)(origine.y / GRID) * GRID - 1;
	else
		npoint.y = (int)(origine.y / GRID) * GRID + GRID;

	npoint.x = origine.x + (npoint.y - origine.y) / tan(angle);
	return (npoint);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int		checkWallHorizontal(t_coor point)
{
	int y = point.y;
	int x = point.x;

	if (y >= 0 && y < HEIGHT * GRID)
	{
		if (map[(int)(y / GRID)][(int)(x / GRID)] == '1')
			return (1);
		if (y - 1 >= 0 && map[(int)((y - 1) / GRID)][(int)(x / GRID)] == '1')
			return (1);
		if (y + 1 < HEIGHT * GRID && map[(int)((y + 1) / GRID)][(int)(x / GRID)] == '1')
			return (1);
	}
	return (0);
}

int		checkWallVertical(t_coor point)
{
	int y = point.y;
	int x = point.x;

	if (x >= 0 && x < LENGTH * GRID)
	{
		if (map[(int)(y / GRID)][(int)(x / GRID)] == '1')
			return (1);
		if (x - 1 >= 0 && map[(int)(y / GRID)][(int)((x - 1) / GRID)] == '1')
			return (1);
		if (x + 1 < LENGTH * GRID && map[(int)(y / GRID)][(int)((x + 1) / GRID)] == '1')
			return (1);
	}
	return (0);
}

/*	selon un point (ex ray.b (qui est une rotation de img.a)) et une origine (ex milieu trinagle)
 *	prolonge la droite point origine, jusqu'a atteindre un mur
 *	verifie la detection de mur avec xa et ya (detection horizontal et vertical)
 *	renvoie les coor juste avant le mur
*/

t_coor 	ray(t_frame *img, t_coor point, t_coor origine, int color)
{
	t_coor pointXA;
	t_coor pointYA;
	double angle;


	angle = getAnlge(point, origine);

	double xa = (double)GRID / tan(angle);
	double ya = (double)GRID * tan(angle);

	pointXA = firstIntersectionHorizontal(point, origine, angle);
	pointYA = firstIntersectionVertical(point, origine, angle);

	double py = origine.y - point.y;
	double px = origine.x - point.x;


	while (pointXA.x >= 0 && pointXA.x < LENGTH * GRID &&
			pointXA.y >= 0 && pointXA.y < HEIGHT * GRID && 
			!checkWallHorizontal(pointXA))
	{
		if (py > 0)
		{
			pointXA.x += -xa;
			pointXA.y += -GRID;
		}
		else
		{
			pointXA.x += xa;
			pointXA.y += GRID;
		} 
	}

	if (pointXA.x < 0)
		pointXA.x = 0;

	if (pointXA.x >= LENGTH * GRID)
		pointXA.x = LENGTH * GRID - 1;

	if (pointXA.y < 0)
		pointXA.y = 0;

	if (pointXA.y >= HEIGHT * GRID)
		pointXA.y = HEIGHT * GRID - 1;


	while (pointYA.x >= 0 && pointYA.x < LENGTH * GRID &&
			pointYA.y >= 0 && pointYA.y < HEIGHT * GRID && 
			!checkWallVertical(pointYA))
	{
		if (px > 0)
		{
			pointYA.y +=  -ya;
			pointYA.x += -GRID;
		}
		else
		{
			pointYA.y += ya;
			pointYA.x += GRID;
		}
	}
 
	
	if (pointYA.x < 0)
		pointYA.x = 0;

	if (pointYA.x >= LENGTH * GRID)
		pointYA.x = LENGTH * GRID - 1;

	if (pointYA.y < 0)
		pointYA.y = 0;

	if (pointYA.y >= HEIGHT * GRID)
		pointYA.y = HEIGHT * GRID - 1;
			
	(void)color;


	double lxa = getLengthRay(pointXA, origine, angle);
	double lya = getLengthRay(pointYA, origine, angle);
	(void)color;

	if (lxa < lya)
		put_pixel(img, pointXA.y, pointXA.x, color);
	else if (lxa > lya)
		put_pixel(img, pointYA.y, pointYA.x, color);

	return (point);
}



void	castRays(t_frame *img, t_frame *img2, t_coor origine, double nbrays)
{
    t_coor      bn;

	(void) img2;

	double current_angle = 60;

	double nbpixel = LENGTH * GRID;
    double      angleinc = (current_angle / nbpixel); 

    int         i = 0;
	(void)nbrays;
	(void)origine;

	bn.x = img->ray.b.x;
	bn.y = img->ray.b.y;

	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bn.x, &bn.y, img->triangle.milieu);
		ray(img, bn, origine, 0x00FFFFFF);
		i++;
	}
}


void	erasecastRays(t_frame *img, t_frame *img2, t_coor origine, double nbrays)
{
    t_coor      bn;

	(void) img2;

	double current_angle = 60;

	double nbpixel = LENGTH * GRID;
    double      angleinc = (current_angle / nbpixel); 

    int         i = 0;
	(void)nbrays;
	(void)origine;

	bn.x = img->ray.b.x;
	bn.y = img->ray.b.y;

	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bn.x, &bn.y, img->triangle.milieu);
		ray(img, bn, origine, 0);
		i++;
	}
}

