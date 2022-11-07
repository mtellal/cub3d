/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:05:17 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/21 16:20:44 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_player *player, int inc_x, int inc_y)
{
	player->north.x += inc_x;
	player->north.y += inc_y;
	player->left.x += inc_x;
	player->left.y += inc_y;
	player->pos.y += inc_y;
	player->pos.x += inc_x;
}

void	moveup(t_data *data, t_frame *img, t_coor dda_inc)
{
	int			inc_x;
	int			inc_y;
	t_player	*p;
	(void)img;

	inc_x = dda_inc.x * GRID * 0.008;
	inc_y = dda_inc.y * GRID * 0.008;
	p = &data->p;
	if (data->map[(int)((p->pos.y + (p->projection * dda_inc.y) + inc_y) / GRID)]
			[(int)((p->pos.x + (p->projection * dda_inc.x) + inc_x) / GRID)] != '1' && 
			data->map[(int)((p->pos.y + inc_y) / GRID)]
			[(int)((p->pos.x + inc_x) / GRID)] != '1')
		move_player(p, inc_x, inc_y);
}

void	movedown(t_data *data, t_frame *img, t_coor dda_inc)
{
	int			inc_x;
	int			inc_y;
	t_player	*p;
	(void)img;

	inc_x = -dda_inc.x * GRID * 0.008;
	inc_y = -dda_inc.y * GRID * 0.008;
	p = &data->p;
	if (data->map[(int)((p->pos.y + (p->projection * -dda_inc.y) + inc_y) / GRID)]
			[(int)((p->pos.x + (p->projection * -dda_inc.x) + inc_x) / GRID)] != '1' && 
			data->map[(int)((p->pos.y + inc_y) / GRID)]
			[(int)((p->pos.x + inc_x) / GRID)] != '1')
		move_player(p, inc_x, inc_y);
}

void	moverigth(t_data *data, t_frame *img, t_coor dda_inc)
{
	int			inc_x;
	int			inc_y;
	t_player	*p;
	(void)img;

	inc_x = dda_inc.x * GRID * 0.008;
	inc_y = dda_inc.y * GRID * 0.008;
	p = &data->p;
	if (data->map[(int)((p->pos.y + (p->projection * dda_inc.y) + inc_y) / GRID)]
			[(int)((p->pos.x + (p->projection * dda_inc.x) + inc_x) / GRID)] != '1' && 
			data->map[(int)((p->pos.y + inc_y) / GRID)]
			[(int)((p->pos.x + inc_x) / GRID)] != '1')
		move_player(p, inc_x, inc_y);
}

void	moveleft(t_data *data, t_frame *img, t_coor dda_inc)
{
	int			inc_x;
	int			inc_y;
	t_player	*p;
	(void)img;

	inc_x = -dda_inc.x * GRID * 0.008;
	inc_y = -dda_inc.y * GRID * 0.008;
	p = &data->p;
	if (data->map[(int)((p->pos.y + (p->projection * -dda_inc.y) + inc_y) / GRID)]
			[(int)((p->pos.x + (p->projection * -dda_inc.x) + inc_x) / GRID)] != '1' && 
			data->map[(int)((p->pos.y + inc_y) / GRID)]
			[(int)((p->pos.x + inc_x) / GRID)] != '1')
		move_player(p, inc_x, inc_y);
}
