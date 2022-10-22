/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:35:19 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 14:30:12 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(void *data)
{
	move(data);
	return (0);
}

int	keypressed(int keycode, t_data *data)
{
	if (keycode == UP)
		data->img2d.move |= U;
	if (keycode == DOWN)
		data->img2d.move |= D;
	if (keycode == RIGHT)
		data->img2d.move |= R;
	if (keycode == LEFT)
		data->img2d.move |= L;
	if (keycode == VRIGHT)
		data->img2d.move |= VR;
	if (keycode == VLEFT)
		data->img2d.move |= VL;
	if (keycode == XK_Escape)
		exit_game(data);
	return (0);
}

int	keyreleased(int keycode, t_frame *img2d)
{
	if (keycode == UP)
		img2d->move &= ~U;
	if (keycode == DOWN)
		img2d->move &= ~D;
	if (keycode == RIGHT)
		img2d->move &= ~R;
	if (keycode == LEFT)
		img2d->move &= ~L;
	if (keycode == VRIGHT)
		img2d->move &= ~VR;
	if (keycode == VLEFT)
		img2d->move &= ~VL;
	return (0);
}
