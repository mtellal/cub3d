/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:17:02 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/21 16:05:36 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_and_display(t_data *d)
{
	d->rays = castrays(d);
	displayrays(d, d->rays);
	draw_triangle(&d->img2d, d->img2d.triangle, PLAYERCOLOR);
	minimap(d, &d->img2d, &d->img3d);
	if (d && d->mlx && d->img3d.window && d->img3d.img)
		mlx_put_image_to_window(d->mlx, d->img3d.window, d->img3d.img, 0, 0);
}

void	eraseprecedentstatemovement(t_data *data)
{
	if (data->rays)
	{
		draw_triangle(&data->img2d, data->img2d.triangle, 0);
		free_rays(data->rays, data->img3d.width);
		data->rays = NULL;
	}
}

void	move(t_data *data)
{
	t_frame	*img2d;
	t_coor	direction_incup;
	t_coor	direction_incrigth;

	img2d = &data->img2d;
	if (!img2d->move)
		return ;
	eraseprecedentstatemovement(data);
	direction_incup = coorline(img2d->triangle.a, img2d->triangle.milieu);
	direction_incrigth = coorline(img2d->triangle.c, img2d->triangle.b);
	if (img2d->move & U)
		moveup(data, img2d, direction_incup);
	if (img2d->move & D)
		movedown(data, img2d, direction_incup);
	if (img2d->move & R)
		moverigth(data, img2d, direction_incrigth);
	if (img2d->move & L)
		moveleft(data, img2d, direction_incrigth);
	if (img2d->move & VR)
		movevrigth(img2d);
	if (img2d->move & VL)
		movevleft(img2d);
	cast_and_display(data);
}
