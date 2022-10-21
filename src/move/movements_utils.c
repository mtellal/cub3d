/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:18:24 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/21 16:18:32 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	addpixelx(t_triangle *t, double pixel)
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

void	addpixely(t_triangle *t, double pixel)
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

int	checkpointwall(t_data *data, t_coor point, t_coor dda_inc)
{
	if (data->map[(int)((point.y + dda_inc.y + 1) / GRID)]
			[(int)((point.x + dda_inc.x + 1) / GRID)] == '1')
		return (1);
	return (0);
}

int	checkcoorsquare(t_data *data, t_coor c1, t_coor c2, t_coor dda_inc)
{
	if (!checkpointwall(data, c1, dda_inc)
		&& !checkpointwall(data, c2, dda_inc))
		return (1);
	return (0);
}
