/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:05:17 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/09 11:26:43 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_player *player, int inc_x, int inc_y)
{
	player->pos.x += inc_x;
	player->pos.y += inc_y;
	player->up.x += inc_x;
	player->up.y += inc_y;
	player->down.x += inc_x;
	player->down.y += inc_y;
	player->right.x += inc_x;
	player->right.y += inc_y;
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
	if (check_wall(data, p->up, inc_x, inc_y))
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
	if (check_wall(data, p->down, inc_x, inc_y))
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
	if (check_wall(data, p->right, inc_x, inc_y))
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
	if (check_wall(data, p->left, inc_x, inc_y))
		move_player(p, inc_x, inc_y);
}
