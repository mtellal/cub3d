/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:34:06 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/14 13:34:14 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (origine.x - point.x == 0)
		return (abs_value(origine.y - point.y));
	if (origine.y - point.y == 0)
		return (abs_value(origine.x - point.x));
	return abs_value(abs_value(origine.x - point.x) / cos(angle));
}

int     checkWall(char m[MHEIGHT][MLENGTH], int x, int y)
{
    if (m[x][y] == '1')
        return (1);
    return (0);
}

void    free_rays(t_ray **rays, int l)
{
        int i = 0;
        while (i < l)
        {
                free(rays[i]);
                i++;
        }
        free(rays);
}
