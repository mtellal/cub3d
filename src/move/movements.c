/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:05:17 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/21 10:05:26 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double pixel = 0.08;

///////// MOVEMENTS /////////////

void    moveUP(t_frame *img)
{
    if (img->triangle.a.y - pixel > 0 &&
        img->triangle.b.y - pixel > 0 &&
        img->triangle.c.y - pixel > 0 && 
            !checkWall(map, (img->triangle.ipos.x - (GRID * 0.25)) / GRID, (img->triangle.ipos.y + (GRID / 2)) / GRID))
    {

        img->triangle.a.y -= pixel;
        img->triangle.b.y -= pixel;
        img->triangle.c.y -= pixel;
        img->triangle.milieu.y -= pixel;
        img->triangle.ipos.x -= pixel;
    }
}

void    moveDOWN(t_frame *img)
{
    if (img->triangle.milieu.y + pixel < HEIGHT * GRID && 
            !checkWall(map, (img->triangle.ipos.x  + GRID )/ GRID, (img->triangle.ipos.y + (GRID / 2)) / GRID))
    {
        img->triangle.a.y += pixel;
        img->triangle.b.y += pixel;
        img->triangle.c.y += pixel;
        img->triangle.milieu.y += pixel;
        img->triangle.ipos.x += pixel;
    }
}

void    moveRIGHT(t_frame *img)
{
    if (img->triangle.c.x + pixel < LENGTH * GRID && 
            !checkWall(map, (img->triangle.ipos.x + (GRID / 2)) / GRID, (img->triangle.ipos.y + GRID) / GRID))
    {
        img->triangle.a.x += pixel;
        img->triangle.b.x += pixel;
        img->triangle.c.x += pixel;
        img->triangle.milieu.x += pixel;
        img->triangle.ipos.y += pixel;
    }
}

void    moveLEFT(t_frame *img)
{
    if (img->triangle.b.x >= 0 && 
            !checkWall(map, (img->triangle.ipos.x + (GRID / 2)) / GRID, (img->triangle.ipos.y - (GRID / 4)) / GRID))
    {
        img->triangle.a.x -= pixel;
        img->triangle.b.x -= pixel;
        img->triangle.c.x -= pixel;
        img->triangle.milieu.x -= pixel;
        img->triangle.ipos.y -= pixel;
    }
}