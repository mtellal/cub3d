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

int pixel = 1;

///////// MOVEMENTS /////////////

void    moveUP(t_frame *img)
{
    if (img->triangle.a.y - pixel > 0 &&
        img->triangle.b.y - pixel > 0 &&
        img->triangle.c.y - pixel > 0 && 
            !checkWall(map, (img->triangle.ipos.x - 5) / 20, (img->triangle.ipos.y + 10) / 20))
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
    if (img->triangle.milieu.y + pixel < HEIGHT * 20 && 
            !checkWall(map, (img->triangle.ipos.x  + 20 )/ 20, (img->triangle.ipos.y + 10) / 20))
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
    if (img->triangle.c.x + pixel < LENGTH * 20 && 
            !checkWall(map, (img->triangle.ipos.x + 10) / 20, (img->triangle.ipos.y + 20) / 20))
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
            !checkWall(map, (img->triangle.ipos.x + 10) / 20, (img->triangle.ipos.y - 5) / 20))
    {
        img->triangle.a.x -= pixel;
        img->triangle.b.x -= pixel;
        img->triangle.c.x -= pixel;
        img->triangle.milieu.x -= pixel;
        img->triangle.ipos.y -= pixel;
    }
}