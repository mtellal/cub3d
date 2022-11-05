/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:06:19 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 14:43:25 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	correctfisheye(double length, double cumulangle)
{
	return (length * cos(cumulangle));
}

t_ray	**inittabrays(int nbrays)
{
	int		i;
	t_ray	**rays;

	i = 0;
	rays = malloc(sizeof(t_ray *) * nbrays);
	if (!rays)
		ft_putstr_fd("ERROR RAYS[LENGTH]\n", 1);
	while (i < nbrays)
	{
		rays[i] = (t_ray *)malloc(sizeof(t_ray));
		if (!rays[i])
		{
			ft_putstr_fd("ERROR ALLOCATION RAYS[II]\n", 1);
			exit(1);
		}
		i++;
	}
	return (rays);
}

double	getlengthray(t_coor point,
		t_coor origine, double angle)
{
	int	deg_angle;

	deg_angle = (int)rad2deg(angle);
	if ((int)origine.x == (int)point.x
		|| deg_angle == 90 || deg_angle == 270)
		return (abs_value(origine.y - point.y));
	if ((int)origine.y == (int)point.y
		|| deg_angle == 180 || deg_angle == 360)
		return (abs_value(origine.x - point.x));
	return (abs_value(abs_value(origine.x - point.x) / cos(angle)));
}

double	getanlge(t_coor point, t_coor origine)
{
	double	angle;
	t_coor	ppoint;

	ppoint.x = point.x - origine.x;
	ppoint.y = point.y - origine.y;
	angle = atan(ppoint.y / ppoint.x);
	if (point.y <= origine.y && point.x >= origine.x)
		angle *= -1;
	if (point.y <= origine.y && point.x <= origine.x)
		angle = deg2rad(180) - angle;
	if (point.y >= origine.y && point.x <= origine.x)
		angle = deg2rad(180) - angle;
	if (point.y >= origine.y && point.x >= origine.x)
		angle = deg2rad(360) - angle;
	return (angle);
}

t_coor	coorline(t_coor point, t_coor origine)
{
	double	diff_x;
	double	diff_y;
	double	steps;
	t_coor	abs;
	t_coor	inc;

	diff_x = point.x - origine.x;
	diff_y = point.y - origine.y;
	abs.x = abs_value(diff_x);
	abs.y = abs_value(diff_y);
	if (abs.x > abs.y)
		steps = abs.x;
	else
		steps = abs.y;
	inc.x = diff_x / steps;
	inc.y = diff_y / steps;
	return (inc);
}
