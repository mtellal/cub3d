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

void    addPixelX(t_triangle *t, double pixel)
{
    t->a.x += pixel;
    t->b.x += pixel;
    t->c.x += pixel;
    t->milieu.x += pixel;
    t->ipos.l += pixel;
}

void    addPixelY(t_triangle *t, double pixel)
{
    t->a.y += pixel;
    t->b.y += pixel;
    t->c.y += pixel;
    t->milieu.y += pixel;
    t->ipos.h += pixel;
}

///////// MOVEMENTS /////////////

void    moveUP(t_frame *img)
{
    if (img->triangle.a.y - pixel > 0 &&
        img->triangle.b.y - pixel > 0 &&
        img->triangle.c.y - pixel > 0 && 
            !checkWall(map, (img->triangle.ipos.h + (GRID * 0.2)) / GRID, (img->triangle.ipos.l + (GRID * 0.2)) / GRID) &&
            !checkWall(map, (img->triangle.ipos.h + (GRID * 0.2)) / GRID, (img->triangle.ipos.l + (GRID * 0.8)) / GRID))
    {
        addPixelY(&img->triangle, -pixel);
        addPixelY(&img->ray, -pixel);       
    }
}

void    moveDOWN(t_frame *img)
{
    if (img->triangle.milieu.y + pixel < HEIGHT * GRID && 
            !checkWall(map, (img->triangle.ipos.h  + (GRID * 0.8)) / GRID, (img->triangle.ipos.l + (GRID * 0.2)) / GRID) &&
            !checkWall(map, (img->triangle.ipos.h  + (GRID * 0.9)) / GRID, (img->triangle.ipos.l + (GRID * 0.8)) / GRID))
    {
        addPixelY(&img->triangle, pixel);
        addPixelY(&img->ray, pixel);
    }
}

void    moveRIGHT(t_frame *img)
{
   /*  put_pixel(img, img->triangle.ipos.x + (GRID * 0.2),  img->triangle.ipos.y + (GRID * 0.8), 0x00FFFFFF);
    put_pixel(img, img->triangle.ipos.x + (GRID * 0.8),  img->triangle.ipos.y + (GRID * 0.8), 0x00FFFFFF); */

    if (img->triangle.c.x + pixel < LENGTH * GRID && 
            !checkWall(map, (img->triangle.ipos.h + (GRID * 0.2)) / GRID, (img->triangle.ipos.l + (GRID * 0.8)) / GRID) &&
            !checkWall(map, (img->triangle.ipos.h + (GRID * 0.8)) / GRID, (img->triangle.ipos.l + (GRID * 0.8)) / GRID))
    {
        addPixelX(&img->triangle, pixel);
        addPixelX(&img->ray, pixel);
    }
}

void    moveLEFT(t_frame *img)
{
    if (img->triangle.b.x >= 0 && 
            !checkWall(map, (img->triangle.ipos.h + (GRID * 0.2)) / GRID, (img->triangle.ipos.l + (GRID * 0.2)) / GRID) &&
            !checkWall(map, (img->triangle.ipos.h + (GRID * 0.8)) / GRID, (img->triangle.ipos.l + (GRID * 0.2)) / GRID))
    {
        addPixelX(&img->triangle, -pixel);
        addPixelX(&img->ray, -pixel);
    }
}