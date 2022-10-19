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

double  pixel = 0.1;
double  multiplicator = GRID * 0.03;

void    addPixelX(t_triangle *t, double pixel)
{
    t->no.x += pixel;
    t->ne.x += pixel;
    t->so.x += pixel;
    t->se.x += pixel;

    t->a.x += pixel;
    t->b.x += pixel;
    t->c.x += pixel;

    t->milieu.x += pixel;

    t->ipos.l += pixel;
}

void    addPixelY(t_triangle *t, double pixel)
{
    t->no.y += pixel;
    t->ne.y += pixel;
    t->so.y += pixel;
    t->se.y += pixel;

    t->a.y += pixel;
    t->b.y += pixel;
    t->c.y += pixel;

    t->milieu.y += pixel;

    t->ipos.h += pixel;
}

///////// MOVEMENTS /////////////

int     checkPointWall(t_data *data, t_coor point, t_coor dda_inc)
{
    if (data->map[(int)((point.y + dda_inc.y + 1) / GRID)][(int)((point.x + dda_inc.x + 1) / GRID)] == '1')
        return (1);
    return (0);
}

int checkCoorSquare(t_data *data, t_coor c1, t_coor c2, t_coor dda_inc)
{
    //  verifie si points du triangle sont bien dans la map + pas dans une mur 
    // img->triangle
    if (!checkPointWall(data, c1, dda_inc) &&
        !checkPointWall(data, c2, dda_inc))
        return (1);
    return (0);
}

void    moveUP(t_data *data, t_frame *img, t_coor dda_inc)
{
    if (checkCoorSquare(data, img->triangle.no, img->triangle.ne, dda_inc))
    {
        dda_inc.x *= multiplicator;
        dda_inc.y *= multiplicator;

        addPixelY(&img->triangle, dda_inc.y);
        addPixelX(&img->triangle, dda_inc.x);
        addPixelY(&img->ray, dda_inc.y);
        addPixelX(&img->ray, dda_inc.x);      
    }
}

void    moveDOWN(t_data *data, t_frame *img, t_coor dda_inc)
{
    dda_inc.x *= -1;
    dda_inc.y *= -1;

    if (checkCoorSquare(data, img->triangle.so, img->triangle.se, dda_inc))
    {
        dda_inc.x *= multiplicator;
        dda_inc.y *= multiplicator;

        addPixelY(&img->triangle, dda_inc.y);
        addPixelX(&img->triangle, dda_inc.x);
        addPixelY(&img->ray, dda_inc.y);
        addPixelX(&img->ray, dda_inc.x);      
    }
}

void    moveRIGHT(t_data *data, t_frame *img, t_coor dda_inc)
{
    if (checkCoorSquare(data, img->triangle.ne, img->triangle.se, dda_inc))
    {
        dda_inc.x *= multiplicator;
        dda_inc.y *= multiplicator;

        addPixelY(&img->triangle, dda_inc.y);
        addPixelX(&img->triangle, dda_inc.x);
        addPixelY(&img->ray, dda_inc.y);
        addPixelX(&img->ray, dda_inc.x);      
    }
}

void    moveLEFT(t_data *data, t_frame *img, t_coor dda_inc)
{
    dda_inc.x *= -1;
    dda_inc.y *= -1;

    if (checkCoorSquare(data, img->triangle.no, img->triangle.so, dda_inc))
    {
        dda_inc.x *= multiplicator;
        dda_inc.y *= multiplicator;

        addPixelY(&img->triangle, dda_inc.y);
        addPixelX(&img->triangle, dda_inc.x);
        addPixelY(&img->ray, dda_inc.y);
        addPixelX(&img->ray, dda_inc.x);      
    }
}