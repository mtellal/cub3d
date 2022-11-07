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

void	rotatetriangle(t_triangle *t, double angle)
{
	rotatepoint(angle, &t->a.x, &t->a.y, t->milieu);
	rotatepoint(angle, &t->b.x, &t->b.y, t->milieu);
	rotatepoint(angle, &t->c.x, &t->c.y, t->milieu);
	rotatepoint(angle, &t->no.x, &t->no.y, t->milieu);
	rotatepoint(angle, &t->ne.x, &t->ne.y, t->milieu);
	rotatepoint(angle, &t->so.x, &t->so.y, t->milieu);
	rotatepoint(angle, &t->se.x, &t->se.y, t->milieu);
}

void	rrotatetriangle(t_triangle *t, double angle)
{
	rrotatepoint(angle, &t->a.x, &t->a.y, t->milieu);
	rrotatepoint(angle, &t->b.x, &t->b.y, t->milieu);
	rrotatepoint(angle, &t->c.x, &t->c.y, t->milieu);
	rrotatepoint(angle, &t->no.x, &t->no.y, t->milieu);
	rrotatepoint(angle, &t->ne.x, &t->ne.y, t->milieu);
	rrotatepoint(angle, &t->so.x, &t->so.y, t->milieu);
	rrotatepoint(angle, &t->se.x, &t->se.y, t->milieu);
}

void	movevleft(t_data *d, t_frame *img)
{
	double		angle;
	t_player	*player;
	(void)img;

	player = &d->p;
	angle = deg2rad(GRID * 0.006);
	rotatepoint(angle, &player->north.x, &player->north.y, d->p.pos);
	rotatepoint(angle, &player->left.x, &player->left.y, d->p.pos);
}

void	movevrigth(t_data *d, t_frame *img)
{
	double		angle;
	t_player	*player;
	(void)img;

	player = &d->p;
	angle = deg2rad(GRID * 0.006);
	rrotatepoint(angle, &player->north.x, &player->north.y, d->p.pos);
	rrotatepoint(angle, &player->left.x, &player->left.y, d->p.pos);
}
