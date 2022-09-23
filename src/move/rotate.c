/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:04:06 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/23 11:04:15 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*  rotate X ou Y selon le sens (r)
*/

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


/*  rotate un point selon son origine dans son plan,
 *  ex pour rotate le triangle, son milieu (img->triangle.milieu) fera l'origine du plan.
 *  d'ou le opos_x/y qui sont la redefinition des coor x,y dans le plan origine et non plus dans le tab (map)
*/

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
