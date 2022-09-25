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


void	draw_line(t_frame *img,  t_coor point, t_coor origine)
{
	double diff_x;
	double diff_y;
	double steps;

	diff_x = point.x - origine.x;
	diff_y = point.y - origine.y;

	double abs_x;
	double abs_y;

	abs_x = diff_x;
	abs_y = diff_y;

	if (abs_x < 0)
		abs_x *= -1;
	if (abs_y < 0)
		abs_y *= -1;

	steps = abs_x > abs_y ? abs_x : abs_y;
	
	double xinc;
	double yinc;

	xinc = diff_x / steps;
	yinc = diff_y / steps;

	double x = origine.x;
	double y = origine.y;

	while (map[(int)(y / GRID)][(int)(x / GRID)] != '1' && 
		y >= 0 && y < GRID * HEIGHT && 
		x >= 0 && x < GRID * LENGTH)
	{
		put_pixel(img, y, x, 0x00FFFFFF);
		y += yinc;
		x += xinc;
	}
}


void	erase_line(t_frame *img,  t_coor point, t_coor origine)
{
	double diff_x;
	double diff_y;
	double steps;

	diff_x = point.x - origine.x;
	diff_y = point.y - origine.y;

	double abs_x;
	double abs_y;

	abs_x = diff_x;
	abs_y = diff_y;

	if (abs_x < 0)
		abs_x *= -1;
	if (abs_y < 0)
		abs_y *= -1;

	steps = abs_x > abs_y ? abs_x : abs_y;
	
	double xinc;
	double yinc;

	xinc = diff_x / steps;
	yinc = diff_y / steps;

	double x = origine.x;
	double y = origine.y;

	while (map[(int)(y / GRID)][(int)(x / GRID)] != '1' && 
		y >= 0 && y < GRID * HEIGHT && 
		x >= 0 && x < GRID * LENGTH)
	{
		put_pixel(img, y, x, 0);
		y += yinc;
		x += xinc;
	}

}

void    move(t_frame *img)
{
    if (!img->move)
    	return ;
    erase_triangle(img, img->triangle);
	erase_line(img, img->ray.b, img->triangle.a);
	erase_line(img, img->ray.c, img->triangle.a);
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
	draw_triangle(img, img->triangle);
   /*  put_pixel(img, img->triangle.milieu.y, img->triangle.milieu.x, 0x00FFFFFF);
	put_pixel(img, img->ray.b.y, img->ray.b.x, 0x00FFFFFF); */
	//put_pixel(img, img->ray.c.y, img->ray.c.x, 0x00FFFFFF);
	//put_pixel(img, img->ray.a.y, img->ray.a.x, 0x00F0FFFF);
	//put_pixel(img, img->ray.ipos.x, img->ray.ipos.y - 50, 0x00FFFFFF);
	draw_line(img, img->ray.b, img->triangle.a);
	draw_line(img, img->ray.c, img->triangle.a);
    push_frame(img);
} 

