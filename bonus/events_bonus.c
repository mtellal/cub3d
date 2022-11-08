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
		data->p.move |= U;
	if (keycode == DOWN)
		data->p.move |= D;
	if (keycode == RIGHT)
		data->p.move |= R;
	if (keycode == LEFT)
		data->p.move |= L;
	if (keycode == VRIGHT)
		data->p.move |= VR;
	if (keycode == VLEFT)
		data->p.move |= VL;
	if (keycode == XK_Escape)
		exit_game(data);
	return (0);
}

int	keyreleased(int keycode, t_data *data)
{
	if (keycode == UP)
		data->p.move &= ~U;
	if (keycode == DOWN)
		data->p.move &= ~D;
	if (keycode == RIGHT)
		data->p.move &= ~R;
	if (keycode == LEFT)
		data->p.move &= ~L;
	if (keycode == VRIGHT)
		data->p.move &= ~VR;
	if (keycode == VLEFT)
		data->p.move &= ~VL;
	return (0);
}
