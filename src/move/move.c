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

	w.size = GRID;
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

void	erase_triangle(t_frame *img, t_triangle triangle)
{
 	t_coor	point;
	int	i = triangle.ipos.y;
	int	j = triangle.ipos.x;

	while (i < triangle.ipos.y + GRID)
	{
		j = 0;
		while (j < triangle.ipos.x + GRID)
		{
			point.x = i;
			point.y = j;
			if (dansLeTriangle(point, triangle))
				put_pixel(img, j, i, 0);
			j++;
		}
		i++;
	}

}

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

