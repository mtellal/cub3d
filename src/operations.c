/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:21:29 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/19 16:21:41 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	formule mathematique pour trouver si un point est inclus dans un triangle
 *	forumle utilisee pour re/display le triangle avec ou sans rotation
 */

float barycentre (t_coor p1, t_coor p2, t_coor p3)
{
    return (float)((p1.x - p3.x) * (p2.y - p3.y)) - (float)((p2.x - p3.x) * (p1.y - p3.y));
}
 
int dansLeTriangle (t_coor pt, t_triangle t)
{
    int b1, b2, b3;
 
	b1 = 0;
	b2 = 0;
	b3 = 0;
    if (barycentre(pt, t.a, t.b) < 0)
		b1 = 1;
	if (barycentre(pt, t.b, t.c) < 0)
		b2 = 1;
	if (barycentre(pt, t.c, t.a) < 0)
		b3 = 1;
 
    return ((b1 == b2) && (b2 == b3));
}