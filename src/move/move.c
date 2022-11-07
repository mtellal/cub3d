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
	if (d && d->mlx && d->img3d.window && d->img3d.img)
		mlx_put_image_to_window(d->mlx, d->img3d.window, d->img3d.img, 0, 0);
}

void	eraseprecedentstatemovement(t_data *data)
{
	if (data->rays)
	{
		free_rays(data->rays, data->img3d.width);
		data->rays = NULL;
	}
}

void	move(t_data *data)
{
	t_frame		*img2d;
	t_player	*p;
	t_coor	direction_incup;
	t_coor	direction_incrigth;

	img2d = &data->img2d;
	p = &data->p;
	if (!data->move)
		return ;
	eraseprecedentstatemovement(data);

	direction_incup = coorline(p->north, p->pos);
	direction_incrigth = coorline(p->left, p->pos);

	if (data->move & U)
		moveup(data, img2d, direction_incup);
	if (data->move & D)
		movedown(data, img2d, direction_incup);
	if (data->move & R)
		moverigth(data, img2d, direction_incrigth);
	if (data->move & L)
		moveleft(data, img2d, direction_incrigth);
	if (data->move & VR)
		movevrigth(data, img2d);
	if (data->move & VL)
		movevleft(data, img2d);
	cast_and_display(data);
}
