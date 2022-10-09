/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:28:19 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/06 18:28:26 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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

/*	dda algotirthm applique de origine (milieu du triangle) a point (ray->b/c qui sont la rotation de a +/-45 deg, ou un autre point)
 *  return les coor a incrementer (x, y) pour projeter/continuer la droite
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

// sens normal donc de 0 a 360 deg avec rotate()

double	getAnlge(t_coor point, t_coor origine)
{
	t_coor ppoint;

	ppoint.x = point.x - origine.x;
	ppoint.y = point.y - origine.y;

	double angle = atan(ppoint.y / ppoint.x);
	if (point.y <= origine.y && point.x >= origine.x)
		angle *= -1;
	if (point.y <= origine.y && point.x <= origine.x)
		angle = deg2rad(180) - angle;
	if (point.y >= origine.y && point.x <= origine.x)
		angle = deg2rad(180) - angle;
	if (point.y >= origine.y && point.x >= origine.x)
		angle = deg2rad(360) - angle;

    return angle;
}

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


double	getLengthRay(t_coor point, t_coor origine, double angle)
{
	return abs_value(abs_value(origine.x - point.x) / cos(angle));
}