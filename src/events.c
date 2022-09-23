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

int	handle_input(void *img)
{
	move(img);
	return (0);
}

/*	ajoute une puissance de 2 au masque, correspondant a un mouvement 
*/

int keyPressed(int keycode, t_frame *img)
{
	(void)img;
	if (keycode == UP)
		img->move |= U;
	if (keycode == DOWN)
		img->move |= D;
	if (keycode == RIGHT)
		img->move |= R;
	if (keycode == LEFT)
		img->move |= L;
	if (keycode == VRIGHT)
		img->move |= VR;
	if (keycode == VLEFT)
		img->move |= VL;

	return (0);
}

/*	supprime du masque un mouvement, lorsque la touche est relachee 
*/

int keyReleased(int keycode, t_frame *img)
{
	if (keycode == UP)
		img->move &= ~U;
	if (keycode == DOWN)
		img->move &= ~D;
	if (keycode == RIGHT)
		img->move &= ~R;
	if (keycode == LEFT)
		img->move &= ~L;
	if (keycode == VRIGHT)
		img->move &= ~VR;
	if (keycode == VLEFT)
		img->move &= ~VL;
	return (0);
}
