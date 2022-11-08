/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:05:17 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/08 16:48:43 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_player *player, int inc_x, int inc_y)
{
	player->pos.x += inc_x;
	player->pos.y += inc_y;
	player->up.x += inc_x;
	player->up.y += inc_y;
	player->left.x += inc_x;
	player->left.y += inc_y;
}

void	moveup(t_data *data, t_coor dda_inc)
{
	int			inc_x;
	int			inc_y;
	t_player	*p;

	inc_x = dda_inc.x * GRID * 0.08;
	inc_y = dda_inc.y * GRID * 0.08;
	p = &data->p;
	if (data->map[(int)((p->pos.y + (inc_y * 2)) / GRID)]
		[(int)((p->pos.x + (inc_x * 2)) / GRID)] != '1' &&
		data->map[(int)((p->pos.y + inc_y) / GRID)]
		[(int)((p->pos.x + inc_x) / GRID)] != '1')
		move_player(p, inc_x, inc_y);
}

void	movedown(t_data *data, t_coor dda_inc)
{
	int			inc_x;
	int			inc_y;
	t_player	*p;

	inc_x = -dda_inc.x * GRID * 0.08;
	inc_y = -dda_inc.y * GRID * 0.08;
	p = &data->p;
	if (data->map[(int)((p->pos.y + (inc_y * 2)) / GRID)]
		[(int)((p->pos.x + (inc_x * 2)) / GRID)] != '1' &&
		data->map[(int)((p->pos.y + inc_y) / GRID)]
		[(int)((p->pos.x + inc_x) / GRID)] != '1')
		move_player(p, inc_x, inc_y);
}

void	moverigth(t_data *data, t_coor dda_inc)
{
	int			inc_x;
	int			inc_y;
	t_player	*p;

	inc_x = dda_inc.x * GRID * 0.08;
	inc_y = dda_inc.y * GRID * 0.08;
	p = &data->p;
	if (data->map[(int)((p->pos.y + (inc_y * 2)) / GRID)]
		[(int)((p->pos.x + (inc_x * 2)) / GRID)] != '1' &&
		data->map[(int)((p->pos.y + inc_y) / GRID)]
		[(int)((p->pos.x + inc_x) / GRID)] != '1')
		move_player(p, inc_x, inc_y);
}

void	moveleft(t_data *data, t_coor dda_inc)
{
	int			inc_x;
	int			inc_y;
	t_player	*p;

	inc_x = -dda_inc.x * GRID * 0.08;
	inc_y = -dda_inc.y * GRID * 0.08;
	p = &data->p;
	if (data->map[(int)((p->pos.y + (inc_y * 2)) / GRID)]
		[(int)((p->pos.x + (inc_x * 2)) / GRID)] != '1' &&
		data->map[(int)((p->pos.y + inc_y) / GRID)]
		[(int)((p->pos.x + inc_x) / GRID)] != '1')
		move_player(p, inc_x, inc_y);
}
