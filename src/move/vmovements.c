/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmovements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:06:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/21 16:34:05 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *player, double angle, int reverse)
{
	if (!reverse)
	{
		rotatepoint(angle, &player->up.x, &player->up.y, player->pos);
		rotatepoint(angle, &player->left.x, &player->left.y, player->pos);
	}
	else
	{
		rrotatepoint(angle, &player->up.x, &player->up.y, player->pos);
		rrotatepoint(angle, &player->left.x, &player->left.y, player->pos);
	}
}

void	movevleft(t_data *d)
{
	double		angle;
	t_player	*player;

	player = &d->p;
	angle = deg2rad(GRID * 0.03);
	rotate_player(player, angle, 0);
}

void	movevrigth(t_data *d)
{
	double		angle;
	t_player	*player;

	player = &d->p;
	angle = deg2rad(GRID * 0.03);
	rotate_player(player, angle, 1);
}
