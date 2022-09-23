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

/*  rotate chaque point du triangle
*/

double  deg2rad(double degrees)
{
    return (degrees * (M_PI / 180));
}

double  rad2deg(double radians)
{
    return (radians * (180 / M_PI));
}   

// column = 35
// fov = deg2rad(60);

//  rayangle += fov / column

void    moveVLEFT(t_frame *img)
{    
    double  angle = deg2rad(0.3);

    rotatePoint(angle, &img->triangle.a.x, &img->triangle.a.y, img->triangle.milieu);

    rotatePoint(angle, &img->triangle.b.x, &img->triangle.b.y, img->triangle.milieu);

    rotatePoint(angle, &img->triangle.c.x, &img->triangle.c.y, img->triangle.milieu);
}

void    moveVRIGHT(t_frame *img)
{
    double		angle = deg2rad(0.3);

    rrotatePoint(angle, &img->triangle.a.x, &img->triangle.a.y, img->triangle.milieu);

    rrotatePoint(angle, &img->triangle.b.x, &img->triangle.b.y, img->triangle.milieu);

    rrotatePoint(angle, &img->triangle.c.x, &img->triangle.c.y, img->triangle.milieu);
}
