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

void    rotateTriangle(t_triangle *t, double angle)
{
    rotatePoint(angle, &t->a.x, &t->a.y, t->milieu);
    rotatePoint(angle, &t->b.x, &t->b.y, t->milieu);
    rotatePoint(angle, &t->c.x, &t->c.y, t->milieu);

    // collisions
    rotatePoint(angle, &t->no.x, &t->no.y, t->milieu);
    rotatePoint(angle, &t->ne.x, &t->ne.y, t->milieu);
    rotatePoint(angle, &t->so.x, &t->so.y, t->milieu);
    rotatePoint(angle, &t->se.x, &t->se.y, t->milieu);
}

void    rrotateTriangle(t_triangle *t, double angle)
{
    rrotatePoint(angle, &t->a.x, &t->a.y, t->milieu);
    rrotatePoint(angle, &t->b.x, &t->b.y, t->milieu);
    rrotatePoint(angle, &t->c.x, &t->c.y, t->milieu);

    // collisions
    rrotatePoint(angle, &t->no.x, &t->no.y, t->milieu);
    rrotatePoint(angle, &t->ne.x, &t->ne.y, t->milieu);
    rrotatePoint(angle, &t->so.x, &t->so.y, t->milieu);
    rrotatePoint(angle, &t->se.x, &t->se.y, t->milieu);


}

double a = GRID * 0.007;

void    moveVLEFT(t_frame *img)
{    
    double  angle = deg2rad(a);

    rotateTriangle(&img->triangle, angle);

}

void    moveVRIGHT(t_frame *img)
{
    double		angle = deg2rad(a);

    rrotateTriangle(&img->triangle, angle);
}
