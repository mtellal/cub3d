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

	//right
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

	//displayCoor(ppoint);

	//face up 
	if (point.y < origine.y)
	{
		npoint.y = floor(origine.y / GRID) * GRID;
		//ft_putstr_fd("face up\n", 1);
	}
	else
	{
		npoint.y = floor(origine.y / GRID) * GRID + GRID;
		//ft_putstr_fd("face down\n", 1);
	}
	npoint.x = origine.x + ((origine.y - npoint.y) / tan(angle));
	return (npoint);
}




t_coor	horizontalCast(t_coor point, t_coor origine, double angle)
{
	(void)angle;
	
	t_coor pointXA = firstIntersectionHorizontal(point, origine, angle);

	
	double xstep = (double)GRID / tan(angle);
	double ystep = GRID;

	//right
	if (origine.x > point.x && xstep > 0)
		xstep *= -1;
	else if (origine.x < point.x && xstep < 0)
		xstep *= -1;


	if (origine.y > point.y)
		ystep *= -1;

	while (pointXA.x >= 0 && pointXA.x < LENGTH * GRID &&
			pointXA.y >= 0 && pointXA.y < HEIGHT * GRID)
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

	if (point.x < origine.x)
		xstep *= -1;

	if (point.y < origine.y && ystep > 0)
		ystep *= -1;
	if (point.y > origine.y && ystep < 0)
		ystep *= -1;

	/* if (point.x < origine.x)
		pointYA.x--; */

	while (pointYA.x >= 0 && pointYA.x < LENGTH * GRID &&
			pointYA.y >= 0 && pointYA.y < HEIGHT * GRID)
	{
		if (map[(int)(pointYA.y / GRID)][(int)(pointYA.x / GRID)] == '1' || 
			(xstep < 0 && map[(int)(pointYA.y / GRID)][(int)((pointYA.x - 1) / GRID)] == '1'))
			break ;
		pointYA.y += ystep;
		pointYA.x += xstep;
	}

	return (pointYA);
}

int		inMap(t_coor point)
{
	if (point.x >= 0 && point.x < LENGTH * GRID &&
		point.y >= 0 && point.y < HEIGHT * GRID)
		return (1);
	return (0);
}


/*	selon un point (ex ray.b (qui est une rotation de img.a)) et une origine (ex milieu trinagle)
 *	prolonge la droite point origine, jusqu'a atteindre un mur
 *	verifie la detection de mur avec xa et ya (detection horizontal et vertical)
 *	renvoie les coor juste avant le mur
*/

double 	ray(t_frame *img, t_coor point, t_coor origine, int color, double angle)
{
	(void)img;

	t_coor pointXA = horizontalCast(point, origine, angle);
	t_coor pointYA = verticalCast(point, origine, angle);
			
	(void)color;


	double lxa = getLengthRay(pointXA, origine, angle);
	double lya = getLengthRay(pointYA, origine, angle);


	(void)color;


	if (round(lxa) < round(lya))
	{
		put_pixel(img, pointXA.y, pointXA.x, color);
		return (lxa);
	}
	else 
	{
		put_pixel(img, pointYA.y, pointYA.x, color);
		return (lya);
	}
	return (-1);
}


void	castRays(t_frame *img, t_frame *img2, t_coor origine, double nbrays, int color)
{
    t_coor      bn;

	(void) img2;

	double current_angle = 60;

	double nbpixel = LENGTH * GRID;
    double      angleinc = deg2rad(current_angle / nbpixel); 

	double angle = getAnlge(img->ray.c, origine);

    int         i = 0;
	(void)nbrays;
	(void)origine;

	bn.x = img->ray.c.x;
	bn.y = img->ray.c.y;


	while (i < 100)
	{
		double length = ray(img, bn, origine, color, angle);
		rotatePoint(angleinc, &bn.x, &bn.y, img->triangle.milieu);
		angle += angleinc;
		//put_pixel(img, bn.y, bn.x, color);
		(void)length;

		i++;
	}
}



