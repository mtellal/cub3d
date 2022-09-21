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

void    refillWalls(t_frame *img, char m[14][35])
{
    int i = 0;
	int j = 0;
	t_wall	w;

	w.size = 20;
	w.color = 0x00B0FF00;

	while (i < HEIGHT)
	{
		j = 0;
		while (j < LENGTH)
		{
			if (m[i][j] == '1')
                draw_wall(img, w, i * w.size, j * w.size);
            j++;
		}
		i++;
	}
}

//////////////  VMOVEMENTS  //////

void    moveVRIGHT(t_frame *img)
{
    double  angle = 10;

    double	apos_x = img->triangle.milieu.x - img->triangle.a.x;
    double	apos_y = img->triangle.milieu.y - img->triangle.a.y;

    img->triangle.a.x = (apos_x * cos(angle)) + (apos_y * -sin(angle));
    img->triangle.a.x += img->triangle.milieu.x;

    img->triangle.a.y = (apos_x * sin(angle)) + (apos_y* cos(angle));
    img->triangle.a.y += img->triangle.milieu.y;


    double	bpos_x = img->triangle.milieu.x - img->triangle.b.x;
    double	bpos_y = img->triangle.milieu.y - img->triangle.b.y;

    img->triangle.b.x = (bpos_x * cos(angle)) + (bpos_y * -sin(angle));
    img->triangle.b.x += img->triangle.milieu.x;

    img->triangle.b.y = (bpos_x * sin(angle)) + (bpos_y * cos(angle));
    img->triangle.b.y += img->triangle.milieu.y;


    double	cpos_x = img->triangle.milieu.x - img->triangle.c.x;
    double	cpos_y = img->triangle.milieu.y - img->triangle.c.y;

    img->triangle.c.x = (cpos_x * cos(angle)) + (cpos_y * -sin(angle));
    img->triangle.c.x += img->triangle.milieu.x;

    img->triangle.c.y = (cpos_x * sin(angle)) + (cpos_y* cos(angle));
    img->triangle.c.y += img->triangle.milieu.y;
}

void    moveVLEFT(t_frame *img)
{
    double		angle = 100;

    double	apos_x = img->triangle.milieu.x - img->triangle.a.x;
    double	apos_y = img->triangle.milieu.y - img->triangle.a.y;

    img->triangle.a.x = (apos_x * -cos(angle)) + (apos_y * sin(angle));
    img->triangle.a.x += img->triangle.milieu.x;

    img->triangle.a.y = (apos_x * -sin(angle)) + (apos_y* -cos(angle));
    img->triangle.a.y += img->triangle.milieu.y;


    double	bpos_x = img->triangle.milieu.x - img->triangle.b.x;
    double	bpos_y = img->triangle.milieu.y - img->triangle.b.y;

    img->triangle.b.x = (bpos_x * -cos(angle)) + (bpos_y * sin(angle));
    img->triangle.b.x += img->triangle.milieu.x;

    img->triangle.b.y = (bpos_x * -sin(angle)) + (bpos_y * -cos(angle));
    img->triangle.b.y += img->triangle.milieu.y;


    double	cpos_x = img->triangle.milieu.x - img->triangle.c.x;
    double	cpos_y = img->triangle.milieu.y - img->triangle.c.y;

    img->triangle.c.x = (cpos_x * -cos(angle)) + (cpos_y * sin(angle));
    img->triangle.c.x += img->triangle.milieu.x;

    img->triangle.c.y = (cpos_x * -sin(angle)) + (cpos_y* -cos(angle));
    img->triangle.c.y += img->triangle.milieu.y;
}

void    move(t_frame *img)
{
    if (!img->move)
        return ;
        
    new_frame(img);

    if (img->move & U)
            moveUP(img);
    if (img->move & D)
            moveDOWN(img);
    if (img->move & R)
            moveRIGHT(img);
    if (img->move & L)
            moveLEFT(img);
	draw_triangle(img, img->triangle);
    refillWalls(img, map);
	push_frame(img);
} 

