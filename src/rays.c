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


int		advanceFirstIntersectionY(t_coor point, t_coor origine, t_coor *newpoint)
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

double	getAnlge(t_coor point, t_coor origine)
{
	t_coor ppoint;

	ppoint.x = point.x - origine.x;
	ppoint.y = point.y - origine.y;

	/* ft_putnbr_fd(ppoint.x, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(ppoint.y, 1);
	ft_putstr_fd("\n", 1); */

	return (atan(ppoint.y / ppoint.x));
}

double	distance_xa(t_frame *img,  t_coor point, t_coor origine)
{
	double angle;
	(void)img;
	advanceFirstIntersectionY(point, origine, &point);
	put_pixel(img, point.y, point.x, 0x00FFFFFF);
	angle = getAnlge(point, origine);
	double y = GRID;
	double d = y / tan(angle);
	ft_putnbr_fd((int)d, 1);
	ft_putstr_fd(" ", 1);
	put_pixel(img, point.y - 10, point.x - d, 0x00FFFFFF);
	return (d);
}

double	distance_ya(t_frame *img,  t_coor point, t_coor origine, double xa)
{
	double angle;
	(void)img;
	angle = getAnlge(point, origine);
	return (xa / tan(angle));
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


void	castRays(t_frame *img, t_frame *img2, t_coor origine, double nbrays)
{
    t_coor      bn;
    t_coor_map  ipos;

	(void) img2;
	double      length = 0;
	double current_angle = 60;
	double nbpixel = LENGTH * GRID;
    double      angleinc = (current_angle / nbpixel); 
    int         i = 0;

	//draw_line(img, img->ray.b, origine, &bn, 0x00FFFFFF, &length);
/* 	double distance = distance_xa(img, img->ray.b, origine);
	ft_putnbr_fd(distance, 1);
	ft_putstr_fd(" ", 1);
	distance = distance_ya(img, img->ray.b, origine, distance);
	ft_putnbr_fd(distance, 1);
	ft_putstr_fd("\n", 1); */
	//dda_dvertical(img, img->ray.b, origine);

	t_coor npoint;
	advanceFirstIntersectionY(img->ray.b, origine, &npoint);
	put_pixel(img, npoint.y, npoint.x, 0x00FFFFFF);
	distance_xa(img, img->ray.b, origine);
	//put_pixel(img, npoint.y, npoint.x + xa, 0x00FFFFFF);



	ipos.h = length;
	ipos.l = 0;

   	//double precedentl = 0;

	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bn.x, &bn.y, img->triangle.milieu);
        
      // precedentl = length;
	 /*  	ft_putnbr_fd(bn.x, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(bn.y, 1);
		ft_putstr_fd(" ", 1);
 */
		//draw_square(img2, (2 * HEIGHT * GRID) - ipos.h * 2, 2 * LENGTH * GRID / nbrays, ipos, 0x00F0F568);
		//draw_line(img, bn, origine, &bn, 0x00FFFFFF, &length);
		ipos.h = length;
		ipos.l += ((2 * LENGTH * GRID)) / nbrays;
		i++;
	}
	//ft_putstr_fd("\n", 1);
}


void	erasecastRays(t_frame *img, t_frame *img2, t_coor origine, double nbrays)
{
    t_coor      bn;
    t_coor_map  ipos;

	(void) img2;
	double      length = 0;
	double current_angle = 60;
	double nbpixel = LENGTH * GRID;
    double      angleinc = (current_angle / nbpixel); 
    int         i = 0;

	draw_line(img, img->ray.b, origine, &bn, 0, &length);

	ipos.h = length;
	ipos.l = 0;

	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bn.x, &bn.y, img->triangle.milieu);
		//draw_square(img2, (2 * HEIGHT * GRID) - ipos.h * 2, 2 * LENGTH * GRID / nbrays, ipos, 0);
		//draw_line(img, bn, origine, NULL, 0, &length);
		ipos.h = length;
		ipos.l += ((2 * LENGTH * GRID)) / nbrays;
		i++;
	}
}
