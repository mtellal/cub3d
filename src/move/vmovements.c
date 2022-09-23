/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmovements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:06:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/22 17:06:44 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double      rotateX(double angle, double x, double y, int r)
{
    if (r)
        return (x * -cos(angle) + y * sin(angle));
    return (x * cos(angle) + y * -sin(angle));
}

double      rotateY(double angle, double x, double y, int r)
{
    if (r)
        return (x * -sin(angle) + y * -cos(angle));
    return ((x * sin(angle) + y * cos(angle)));
}

void        rotatePoint(double angle, double *x, double *y, t_coor origine)
{
    double opos_x = *x - origine.x;
    double opos_y = origine.y - *y;

    *x = rotateX(angle, opos_x, opos_y, 0);
    *x += origine.x;
    *y = rotateY(angle, opos_x, opos_y, 0);
    *y = origine.y - *y;
}

void        rrotatePoint(double angle, double *x, double *y, t_coor origine)
{
    double opos_x = origine.x - *x;
    double opos_y = origine.y - *y;

    *x = rotateX(angle, opos_x, opos_y, 1);
    *x += origine.x;
    *y = rotateY(angle, opos_x, opos_y, 1);
    *y += origine.y;
}

void    moveVLEFT(t_frame *img)
{    
    double  angle = 0.003;

    rotatePoint(angle, &img->triangle.a.x, &img->triangle.a.y, img->triangle.milieu);

    rotatePoint(angle, &img->triangle.b.x, &img->triangle.b.y, img->triangle.milieu);

    rotatePoint(angle, &img->triangle.c.x, &img->triangle.c.y, img->triangle.milieu);
}

void    moveVRIGHT(t_frame *img)
{
    double		angle = 0.003;

    rrotatePoint(angle, &img->triangle.a.x, &img->triangle.a.y, img->triangle.milieu);

    rrotatePoint(angle, &img->triangle.b.x, &img->triangle.b.y, img->triangle.milieu);

    rrotatePoint(angle, &img->triangle.c.x, &img->triangle.c.y, img->triangle.milieu);
}
