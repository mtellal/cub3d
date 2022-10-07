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

/////////////////////////////////////////////////////////////////////////////////////

double	distance_xa(t_frame *img,  t_coor point, t_coor origine, t_coor *npoint)
{
	double angle;
	(void)img;
	(void)npoint;

	angle = getAnlge(point, origine);
	*npoint = firstIntersectionHorizontal(point, origine, angle); 
	double d = (double)GRID / tan(angle);
	return (d);
}

double	distance_ya(t_frame *img,  t_coor point, t_coor origine, t_coor *npoint)
{
	double angle;
	(void)img;

	angle = getAnlge(point, origine);
	*npoint = firstIntersectionVertical(point, origine, angle);
	return ((double)GRID * tan(angle));
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

	double ya = distance_ya(img, point, origine, &pointYA);

	double xa = distance_xa(img, point, origine, &pointXA);

	double py = origine.y - point.y;
	double px = origine.x - point.x;

	//put_pixel(img, pointXA.y, pointXA.x, color);
	//put_pixel(img, pointYA.y, pointYA.x, color);


	// find last point in horizontal point (y) with xa diff 

	while (pointXA.x >= 0 && pointXA.x < LENGTH * GRID &&
			pointXA.y >= 0 && pointXA.y < HEIGHT * GRID && !checkWallHorizontal(pointXA))
	{
		//put_pixel(img, pointXA.y, pointXA.x, color); 
			/* ft_putstr_fd("XA ", 1);
			displayCoor(pointXA); */
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
	//ft_putstr_fd("\n\n", 1);

	if (pointXA.x < 0)
		pointXA.x = 0;

	if (pointXA.x >= LENGTH * GRID)
		pointXA.x = LENGTH * GRID - 1;

	if (pointXA.y < 0)
		pointXA.y = 0;

	if (pointXA.y >= HEIGHT * GRID)
		pointXA.y = HEIGHT * GRID - 1;

	//displayCoor(pointYA);

	while (pointYA.x >= 0 && pointYA.x < LENGTH * GRID &&
			pointYA.y >= 0 && pointYA.y < HEIGHT * GRID && !checkWallVertical(pointYA))
	{
		//put_pixel(img, pointYA.y, pointYA.x, color); 
		/* ft_putstr_fd("YA ", 1);
		displayCoor(pointYA); */
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
 
 	//displayCoor(pointYA);
	
	if (pointYA.x < 0)
		pointYA.x = 0;

	if (pointYA.x >= LENGTH * GRID)
		pointYA.x = LENGTH * GRID - 1;

	if (pointYA.y < 0)
		pointYA.y = 0;

	if (pointYA.y >= HEIGHT * GRID)
		pointYA.y = HEIGHT * GRID - 1;
			
	(void)color;


	double lxa = getLengthRay(pointXA, origine);
	double lya = getLengthRay(pointYA, origine);
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

