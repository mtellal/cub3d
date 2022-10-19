/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:35:19 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/23 11:35:30 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	fonction appelee avec loop_hook
 *	update l'image lors des mouvements
 */

int	handle_input(void *data)
{
	move(data);
	return (0);
}

/*	ajoute une puissance de 2 au masque, correspondant a un mouvement 
*/

int keyPressed(int keycode, t_data *data)
{
	if (keycode == UP)
		data->img2D.move |= U;
	if (keycode == DOWN)
		data->img2D.move |= D;
	if (keycode == RIGHT)
		data->img2D.move |= R;
	if (keycode == LEFT)
		data->img2D.move |= L;
	if (keycode == VRIGHT)
		data->img2D.move |= VR;
	if (keycode == VLEFT)
		data->img2D.move |= VL;
	if (keycode == XK_Escape)
		exit_game(data);

	return (0);
}

/*	supprime du masque un mouvement, lorsque la touche est relachee 
*/

int keyReleased(int keycode, t_frame *img2D)
{
	if (keycode == UP)
		img2D->move &= ~U;
	if (keycode == DOWN)
		img2D->move &= ~D;
	if (keycode == RIGHT)
		img2D->move &= ~R;
	if (keycode == LEFT)
		img2D->move &= ~L;
	if (keycode == VRIGHT)
		img2D->move &= ~VR;
	if (keycode == VLEFT)
		img2D->move &= ~VL;
	return (0);
}
