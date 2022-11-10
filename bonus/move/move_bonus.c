/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:17:02 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/10 10:00:09 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_and_display(t_data *d)
{
	d->rays = castrays(d);
	displayrays(d, d->rays);
	minimap(d);
	if (d && d->mlx && d->img3d.window && d->img3d.img)
		mlx_put_image_to_window(d->mlx, d->img3d.window, d->img3d.img, 0, 0);
}

void	eraseprecedentstatemovement(t_data *data)
{
	if (data->rays)
	{
		free_rays(data->rays, WIDTH);
		data->rays = NULL;
	}
}

void	move(t_data *data)
{
	t_player	*p;
	t_coor		direction_incup;
	t_coor		direction_incrigth;

	p = &data->p;
	if (!p->move)
		return ;
	eraseprecedentstatemovement(data);
	direction_incup = coorline(p->up, p->pos);
	direction_incrigth = coorline(p->pos, p->left);
	if (p->move & U)
		moveup(data, direction_incup);
	if (p->move & D)
		movedown(data, direction_incup);
	if (p->move & R)
		moverigth(data, direction_incrigth);
	if (p->move & L)
		moveleft(data, direction_incrigth);
	if (p->move & VR)
		movevrigth(data);
	if (p->move & VL)
		movevleft(data);
	cast_and_display(data);
}
