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

void    moveVRIGHT(t_frame *img)
{    
    double  angle = 0.003;

    double	apos_x = img->triangle.a.x - img->triangle.milieu.x;
    double	apos_y = img->triangle.milieu.y - img->triangle.a.y;

    img->triangle.a.x = (apos_x * cos(angle)) + (apos_y * -sin(angle));
    img->triangle.a.x += img->triangle.milieu.x;

    img->triangle.a.y = (apos_x * sin(angle)) + (apos_y * cos(angle));
    img->triangle.a.y = img->triangle.milieu.y - img->triangle.a.y;
 
    double	bpos_x = img->triangle.b.x - img->triangle.milieu.x;
    double	bpos_y = img->triangle.milieu.y - img->triangle.b.y;

    img->triangle.b.x = (bpos_x * cos(angle)) + (bpos_y * -sin(angle));
    img->triangle.b.x += img->triangle.milieu.x;

    img->triangle.b.y = (bpos_x * sin(angle)) + (bpos_y * cos(angle));
    img->triangle.b.y = img->triangle.milieu.y - img->triangle.b.y;


    double	cpos_x = img->triangle.c.x - img->triangle.milieu.x;
    double	cpos_y = img->triangle.milieu.y - img->triangle.c.y;

    img->triangle.c.x = (cpos_x * cos(angle)) + (cpos_y * -sin(angle));
    img->triangle.c.x += img->triangle.milieu.x;

    img->triangle.c.y = (cpos_x * sin(angle)) + (cpos_y* cos(angle));
    img->triangle.c.y = img->triangle.milieu.y - img->triangle.c.y;
}

void    moveVLEFT(t_frame *img)
{
    double		angle = 0.003;

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
