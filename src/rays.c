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


double	abs_value(double value)
{
	if (value < 0)
		return (-value);
	return (value);
}

/*	dda algotirthm applique de origine (milieu du triangle) a point (ray->b/c qui sont la rotation de a +/-45 deg)
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


void	draw_square(t_frame *img, int h, int l, t_coor_map pos, int color)
{
	int i = 0;
	int j = 0;

    if (h < 50)
            h = 50;

	while (i < h)
	{
		j = 0;
		while (j < l)
		{
				if (color != 0 && (i == 0 || i == h - 1))
					put_pixel(img, i + pos.h, j + pos.l, 0x00FFFFFF);
				else 
					put_pixel(img, i + pos.h, j + pos.l, color);

			j++;
		}
		i++;
	}
}

void	edgeSquare(t_frame *img, int h, int l, t_coor_map pos, int color)
{
	int i = 0;
	int j = 0;
	(void)color;
	if (h < 50)
            h = 50;

	while (i < h)
	{
		j = 0;
		while (j < l)
		{
				/* if (color != 0 && (j == 0 && j == l - 1)) */
					put_pixel(img, i + pos.h, j + pos.l, 0x00FFFFFF);
				/* else 
					put_pixel(img, i + pos.h, j + pos.l, color); */

			j++;
		}
		i++;
	}
}







// advance on the line to the first intersection on y axe (see horizontal detection) 

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
			*newpoint = npoint;
			return (1);
		}
		y += inc.y;
		x += inc.x;
	}	
	if (map[(int)(y / GRID)][(int)(x / GRID)] != '1')
		return (-1);
	return (1);
}


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
			*newpoint = npoint;
			return (1);
		}
		y += inc.y;
		x += inc.x;
	}	
	if (map[(int)(y / GRID)][(int)(x / GRID)] != '1')
		return (-1);
	return (1);
}

// return an angle (radians format) of point in plan x/y with origine to origin

double	getAnlge(t_coor point, t_coor origine)
{
	t_coor ppoint;

	ppoint.x = point.x - origine.x;
	ppoint.y = point.y - origine.y;

	return (atan(ppoint.y / ppoint.x));
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

// y > 0 affichage a 1-2 pixels pres 
// y < 0 affichage parfait 

void	displayXaPoints(t_frame *img, t_coor point, t_coor origine, double distance, int color)
{
	double x = point.x;
	double y = point.y;

	double py = origine.y - point.y;

	while (y >= 0 && y < GRID * HEIGHT && 
		x >= 0 && x < GRID * LENGTH &&
		map[(int)(y / GRID)][(int)(x / GRID)] != '1')
	{
		if (py > 0)
		{
			if (map[(int)((y - 0.1 * GRID) / GRID)][(int)(x / GRID)] == '1')
				return ;
			put_pixel(img, y, x, color);
			y +=  -GRID;
			x += -distance;
		}
		else
		{
			put_pixel(img, y, x, color);
			/* ft_putstr_fd("in ", 1); */
			y += GRID;
			x += distance;
		}
	}
	/* ft_putstr_fd("\n", 1);	  */
}


void	displayYaPoints(t_frame *img, t_coor point, t_coor origine, double distance, int color)
{
	double x = point.x;
	double y = point.y;

	double px = origine.x - point.x;

	while (y >= 0 && y < GRID * HEIGHT && 
		x >= 0 && x < GRID * LENGTH &&
		map[(int)(y / GRID)][(int)(x / GRID)] != '1')
	{
		if (px > 0)
		{
			if (map[(int)(y / GRID)][(int)((x + 0.1 * GRID) / GRID)] == '1')
				return ;
			put_pixel(img, y, x, color);
			y +=  -distance;
			x += -GRID;
		}
		else
		{
			put_pixel(img, y, x, color);
			/* ft_putstr_fd("in ", 1); */
			y += distance;
			x += GRID;
		}
	}
	/* ft_putstr_fd("\n", 1);	  */
}












void	castRays(t_frame *img, t_frame *img2, t_coor origine, double nbrays)
{
    t_coor      bn;

	(void) img2;

	double current_angle = 60;

	double nbpixel = LENGTH * GRID;
    double      angleinc = (current_angle / nbpixel); 

    int         i = 0;


	t_coor npointh;

	double xa = distance_xa(img, img->ray.b, origine, &npointh);
	displayXaPoints(img, npointh, origine, xa, 0x00FFFFFF);

	t_coor npointv;

	double ya = distance_ya(img, img->ray.b, origine, &npointv);
	displayYaPoints(img, npointv, origine, ya, 0x00FFFFFF);


	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bn.x, &bn.y, img->triangle.milieu);
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


	t_coor npointh;

	double xa = distance_xa(img, img->ray.b, origine, &npointh);
	displayXaPoints(img, npointh, origine, xa, 0);

	t_coor npointv;

	double ya = distance_ya(img, img->ray.b, origine, &npointv);
	displayYaPoints(img, npointv, origine, ya, 0);


	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bn.x, &bn.y, img->triangle.milieu);
		i++;
	}
}

