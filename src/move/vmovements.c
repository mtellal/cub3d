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

void    rotateTriangle(t_triangle *t, double angle)
{
    rotatePoint(angle, &t->a.x, &t->a.y, t->milieu);

    rotatePoint(angle, &t->b.x, &t->b.y, t->milieu);

    rotatePoint(angle, &t->c.x, &t->c.y, t->milieu);
}

void    rrotateTriangle(t_triangle *t, double angle)
{
    rrotatePoint(angle, &t->a.x, &t->a.y, t->milieu);

    rrotatePoint(angle, &t->b.x, &t->b.y, t->milieu);

    rrotatePoint(angle, &t->c.x, &t->c.y, t->milieu);
}

void    moveVLEFT(t_frame *img)
{    
    double  angle = deg2rad(0.05);

    rotateTriangle(&img->triangle, angle);
    rotatePoint(angle, &img->ray.b.x, &img->ray.b.y, img->triangle.milieu);
	rotatePoint(angle, &img->ray.c.x, &img->ray.c.y, img->triangle.milieu);

}

void    moveVRIGHT(t_frame *img)
{
    double		angle = deg2rad(0.05);

    rrotateTriangle(&img->triangle, angle);
    rrotatePoint(angle, &img->ray.b.x, &img->ray.b.y, img->triangle.milieu);
	rrotatePoint(angle, &img->ray.c.x, &img->ray.c.y, img->triangle.milieu);
}
