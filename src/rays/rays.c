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

double 	ray(t_frame *img, t_coor point, t_coor origine, int color, double angle, int *poslwall, t_coor *raycoor)
{
	(void)img;
	(void)color;

	t_coor pointXA = horizontalCast(point, origine, angle);
	t_coor pointYA = verticalCast(point, origine, angle);

	double lxa = getLengthRay(pointXA, origine, angle);
	double lya = getLengthRay(pointYA, origine, angle);

	if (round(lxa) < round(lya))
	{
		put_pixel(img, pointXA.y, pointXA.x, color);
		*poslwall = (int)pointXA.x % GRID;
		raycoor->x = pointXA.x;
		raycoor->y = pointXA.y;
		return (lxa);
	}
	else 
	{
		put_pixel(img, pointYA.y, pointYA.x, color);
		*poslwall = (int)pointYA.y % GRID;
		raycoor->x = pointYA.x;
		raycoor->y = pointYA.y;
		return (lya);
	}
	return (-1);
}


//	pour corriger le fish eye d'un rayon, il faut multiplier sa longueur par le cos d'un angle
//	angle du milieu du fov (+/-90deg ou direction du personnage) et le point ou le rayon a touche le mur 

double	correctFishEye(double length, t_coor trianglea, t_coor origine, t_coor first_ray)
{
	double res = getAnlge(trianglea, origine) - getAnlge(first_ray, origine);

	if (res < 0)
		res += deg2rad(360);

	return (length * cos(res));
}

void	castRays(t_data *data, t_frame *img, t_frame *img2, t_coor origine, double nbrays, int color, int color2)
{
	int			i;

	(void) img2;
	(void)nbrays;
	(void)origine;
	(void)color2;
	(void)data;

	i = 0;

	double current_angle = 60;

    double      angleinc = deg2rad(current_angle / (double)(LENGTH)); 

	// angle place a haut droit du triangle (60deg depuis (x,y)(1,0)) comment dans un repere classique
	double angle = getAnlge(img->ray.c, origine);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// la bande ou le rayon a ete touche sur le mur rayon % GRID(check ray())
	int poslwall;

	double plength = 0;
	double length = 0;

	(void)plength;

	//i = nbrays - 2;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ray tout a droite (img->ray.c)
	t_coor first_ray;

	length = ray(img, img->ray.c, origine, color, angle, &poslwall, &first_ray);

	length = correctFishEye(length, img->triangle.a, origine, first_ray);
	displayRays(img2, length, nbrays, color2, i, &data->wall, poslwall);


	while (i < nbrays)
	{
		rotatePoint(angleinc, &first_ray.x, &first_ray.y, img->triangle.milieu);
		angle += angleinc;
		
		if (length)
			plength = length;

		length = ray(img, first_ray, origine, color, angle, &poslwall, &first_ray);

		/* if (plength && abs_value(plength - length) > 10)
		{
			ft_putnbr_fd(length, 1);
			ft_putstr_fd(" ", 1);
			ft_putnbr_fd(plength, 1);
			ft_putstr_fd(" ", 1);
			ft_putnbr_fd(i, 1);
			//ft_putnbr_fd(i, 1);
			ft_putstr_fd("\n", 1);
		} */

		length = correctFishEye(length, img->triangle.a, origine, first_ray);

		/* ft_putnbr_fd(poslwall, 1);
		ft_putstr_fd("\n", 1); */

		displayRays(img2, length, nbrays, color2, i, &data->wall, poslwall);

		i++;
	}
	//ft_putstr_fd("\n", 1);
}



