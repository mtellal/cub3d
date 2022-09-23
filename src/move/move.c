/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:17:02 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/20 09:17:11 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	verifie si le masque est non nul, alors une touche est presse
 *	efface le triangle
 *	call les functions moveX correspondant aux touches pressees, peut etre en meme temps
 *	display le triangle et push l'image dans la fenetre
 */

void    move(t_frame *img)
{
    if (!img->move)
    	return ;
    erase_triangle(img, img->triangle);
    if (img->move & U)
            moveUP(img);
    if (img->move & D)
            moveDOWN(img);
    if (img->move & R)
            moveRIGHT(img);
    if (img->move & L)
            moveLEFT(img);
    if (img->move & VR)
            moveVRIGHT(img);
    if (img->move & VL)
            moveVLEFT(img);
	draw_triangle(img, img->triangle);
    put_pixel(img, img->triangle.milieu.y, img->triangle.milieu.x, 0x00FFFFFF);
    push_frame(img);
} 

