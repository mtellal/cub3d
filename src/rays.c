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

	SEE DOCS http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs

*/

void	displayCoor(t_coor point)
{
	ft_putstr_fd("coor point x/y\n", 1);
	ft_putstr_fd("x = ", 1);
	ft_putnbr_fd(point.x, 1);
	ft_putstr_fd(" y = ", 1);
	ft_putnbr_fd(point.y, 1);
	ft_putstr_fd("\n\n", 1);
}

double	abs_value(double value)
{
	if (value < 0)
		return (-value);
	return (value);
}


// return an angle (radians format) of point in plan x/y with origine to origin

double	getAnlge(t_coor point, t_coor origine)
{
	t_coor ppoint;

	ppoint.x = point.x - origine.x;
	ppoint.y = point.y - origine.y;

	return (atan(ppoint.y / ppoint.x));
}


/*	dda algotirthm applique de origine (milieu du triangle) a point (ray->b/c qui sont la rotation de a +/-45 deg, ou un autre point)
 */

t_coor	coorLine(t_coor point, t_coor origine)
{
	double diff_x;
	double diff_y;
	double steps;

	diff_x = point.x - origine.x;
	diff_y = point.y - origine.y;

	double abs_x;
	double abs_y;

	abs_x = abs_value(diff_x);
	abs_y = abs_value(diff_y);

	steps = abs_x > abs_y ? abs_x : abs_y;
	
	t_coor inc;

	inc.x = diff_x / steps;
	inc.y = diff_y / steps;

	return (inc);
}

/*	display a line from origine to point and beyond
 *	set ray.x/y the final coor of line extension
 *	set length the number of pixel
 */

void	draw_line(t_frame *img,  t_coor point, t_coor origine, t_coor *ray_coor, int color, double *lengthline)
{
	t_coor inc;

	inc = coorLine(point, origine);

	double x = origine.x;
	double y = origine.y;

	double	l = 0;

	while (map[(int)(y / GRID)][(int)(x / GRID)] != '1' && 
		y >= 0 && y < GRID * HEIGHT && 
		x >= 0 && x < GRID * LENGTH)
	{
		put_pixel(img, y, x, color);
		y += inc.y;
		x += inc.x;
		l++;
	}	 
	if (ray_coor)
	{
		ray_coor->x = x;
		ray_coor->y = y;
		
	}
	if (lengthline)
		*lengthline = l;

}


/*	soit un point et une origine, continue la droite (avec dda = coorLine) jusqu'a trouver la premiere intersection horizontal (axe y)
*	sinon renvoie les coor d'un point valied (exemple: y == 0 ou origine collee a un mure sur l'axe y)
*/

int		advanceFirstIntersectionHorizontal(t_coor point, t_coor origine, t_coor *newpoint)
{
	t_coor inc;
	t_coor npoint;

	inc = coorLine(point, origine);

	double x = origine.x;
	double y = origine.y;

	while (map[(int)(y / GRID)][(int)(x / GRID)] != '1' && 
		y >= 0 && y < GRID * HEIGHT && 
		x >= 0 && x < GRID * LENGTH)
	{
		if ((int)y % GRID == 0)
		{	
			npoint.x = x;
			npoint.y = y;
			if (newpoint)
				*newpoint = npoint;
			return (1);
		}
		y += inc.y;
		x += inc.x;
	}	
	if (map[(int)(y / GRID)][(int)(x / GRID)] == '1')
	{
		npoint.x = x;
		npoint.y = y;
		if (newpoint)
			*newpoint = npoint;
	}
	return (1);
}

/*	soit un point et une origine, continue la droite (avec dda = coorLine) jusqu'a trouver la premiere intersection vertical (axe x)
*	sinon renvoie les coor d'un point valied (exemple: x == 0 ou origine collee a un mure sur l'axe x)
*/

int		advanceFirstIntersectionVertical(t_coor point, t_coor origine, t_coor *newpoint)
{
	t_coor inc;
	t_coor npoint;

	inc = coorLine(point, origine);

	double x = origine.x;
	double y = origine.y;

	while (map[(int)(y / GRID)][(int)(x / GRID)] != '1' && 
		y >= 0 && y < GRID * HEIGHT && 
		x >= 0 && x < GRID * LENGTH)
	{
		if ((int)x % GRID == 0)
		{	
			npoint.x = x;
			npoint.y = y;
			if (newpoint)
				*newpoint = npoint;
			return (1);
		}
		y += inc.y;
		x += inc.x;
	}	
	if (map[(int)(y / GRID)][(int)(x / GRID)] == '1')
	{
		npoint.x = x;
		npoint.y = y;
		if (newpoint)
			*newpoint = npoint;
	}
	return (1);
}

// return distance for each point from horizontal perspective 
// see detection horizontal http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs

double	distance_xa(t_frame *img,  t_coor point, t_coor origine, t_coor *npoint)
{
	double angle;
	(void)img;

	advanceFirstIntersectionHorizontal(point, origine, npoint);
	angle = getAnlge(point, origine);
	double d = (double)GRID / tan(angle);
	return (d);
}

double	distance_ya(t_frame *img,  t_coor point, t_coor origine, t_coor *npoint)
{
	double angle;
	(void)img;

	advanceFirstIntersectionVertical(point, origine, npoint);
	angle = getAnlge(point, origine);
	return ((double)GRID * tan(angle));
}



int		checkWallHorizontal(t_coor point)
{
	if (point.y >= 0 && point.y < HEIGHT * GRID)
	{
		if (point.y - (GRID * 0.1) >= 0 && map[(int)((point.y - (GRID * 0.1)) / GRID)][(int)(point.x / GRID)] == '1')
			return (1);
		if (point.y + (GRID * 0.1) < HEIGHT * GRID && map[(int)((point.y + (GRID * 0.1)) / GRID)][(int)(point.x / GRID)] == '1')
			return (2);
	}
	return (0);
}

int		checkWallVertical(t_coor point )
{
	if (point.x >= 0 && point.x < LENGTH * GRID)
	{
		if (point.x - (GRID * 0.1) >= 0 && map[(int)(point.y / GRID)][(int)((point.x - (GRID * 0.1)) / GRID)] == '1')
			return (1);
		if (point.x + (GRID * 0.1) < LENGTH * GRID && map[(int)(point.y / GRID)][(int)((point.x + (GRID * 0.1)) / GRID)] == '1')
			return (2);
	}
	return (0);
}

double	getLengthRay(t_coor point, t_coor origine)
{
	double lx;
	double ly;

	lx = abs_value(origine.x - point.x);
	ly = abs_value(origine.y - point.y);
	return (sqrt((pow(lx, 2) + pow(ly, 2))));
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

	// find last point in horizontal point (y) with xa diff 

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

	//displayCoor(pointYA);

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
 
 	//displayCoor(pointYA);
	
	if (pointYA.x < 0)
		pointYA.x = 0;

	if (pointYA.x >= LENGTH * GRID)
		pointYA.x = LENGTH * GRID - 1;

	if (pointYA.y < 0)
		pointYA.y = 0;

	if (pointYA.y >= HEIGHT * GRID)
		pointYA.y = HEIGHT * GRID - 1;
	
	double lxa = getLengthRay(pointXA, origine);
	double lya = getLengthRay(pointYA, origine);

	if (lxa < lya)
		put_pixel(img, pointXA.y, pointXA.x, color);
	else 
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

