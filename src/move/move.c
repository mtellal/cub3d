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

void    move(t_data *data)
{
	t_frame *img = &data->img;

        if (!img->move)
    	        return ;
        castRays(&data->img, &data->img2, img->triangle.milieu, LENGTH * GRID, 0, 0);
        draw_triangle(img, img->triangle, 0);
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
	//draw_triangle2(img, img->ray);
      /*   put_pixel(img, img->triangle.milieu.y, img->triangle.milieu.x, 0x00FFFFFF);
	put_pixel(img, img->ray.b.y, img->ray.b.x, 0x00FFFFFF);
	put_pixel(img, img->ray.c.y, img->ray.c.x, 0x00FFFFFF);
	put_pixel(img, img->ray.a.y, img->ray.a.x, 0x00F0FFFF); */
	//put_pixel(img, img->ray.ipos.x, img->ray.ipos.y - 50, 0x00FFFFFF);
	castRays(&data->img, &data->img2, img->triangle.milieu, LENGTH * GRID, 0x00FFFFFF, 0x00AF0000);
	draw_triangle(img, img->triangle, img->triangle.color);
        push_frame(img);
        push_frame(&data->img2);
} 

