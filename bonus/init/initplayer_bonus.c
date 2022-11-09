/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initimg2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:09:12 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/07 13:00:10 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_belong(char c, char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i++] == c)
			return (1);
	}
	return (0);
}

void	init_player_pos(t_data *d, int i, int j)
{
	d->p.pos.x = j * GRID + GRID / 2;
	d->p.pos.y = i * GRID + GRID / 2;
	d->p.up.x = d->p.pos.x;
	d->p.up.y = d->p.pos.y - GRID * 0.1;
	d->p.down.x = d->p.pos.x;
	d->p.down.y = d->p.pos.y + GRID * 0.1;
	d->p.right.x = d->p.pos.x + GRID * 0.1;
	d->p.right.y = d->p.pos.y;
	d->p.left.x = d->p.pos.x - GRID * 0.1;
	d->p.left.y = d->p.pos.y;
}

void	init_rotate_player(t_player *p, double angle, int r)
{
	if (!r)
	{
		rotatepoint(deg2rad(angle), &p->up.x, &p->up.y, p->pos);
		rotatepoint(deg2rad(angle), &p->down.x, &p->down.y, p->pos);
		rotatepoint(deg2rad(angle), &p->right.x, &p->right.y, p->pos);
		rotatepoint(deg2rad(angle), &p->left.x, &p->left.y, p->pos);
	}
	else
	{
		rrotatepoint(deg2rad(angle), &p->up.x, &p->up.y, p->pos);
		rrotatepoint(deg2rad(angle), &p->down.x, &p->down.y, p->pos);
		rrotatepoint(deg2rad(angle), &p->right.x, &p->right.y, p->pos);
		rrotatepoint(deg2rad(angle), &p->left.x, &p->left.y, p->pos);
	}
}

void	direction_player(t_player *p, char c)
{
	if (c == 'S')
		init_rotate_player(p, 180, 0);
	else if (c == 'E')
		init_rotate_player(p, 90, 1);
	else if (c == 'W')
		init_rotate_player(p, 90, 0);
}

void	initplayer(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	d->p.move = 0;
	while (i < d->height)
	{
		j = 0;
		while (j < d->len)
		{
			if (ft_belong(d->map[i][j], "NSEW"))
			{
				init_player_pos(d, i, j);
				direction_player(&d->p, d->map[i][j]);
			}
			j++;
		}
		i++;
	}
}
