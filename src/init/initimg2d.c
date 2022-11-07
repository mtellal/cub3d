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
	d->p.north.x = j * GRID + GRID / 2;
	d->p.north.y = i * GRID + GRID / 3;
	d->p.left.x = j * GRID + GRID;
	d->p.left.y = i * GRID + GRID / 2;
	d->p.pos.x = j * GRID + GRID / 2;
	d->p.pos.y = i * GRID + GRID / 2;
	d->p.projection = d->p.pos.y - d->p.north.y;
}

void	init_player(t_data *d, int i, int j, char c)
{
	init_player_pos(d, i, j);
	if (c == 'S')
		rotatepoint(deg2rad(180), &d->p.north.x, &d->p.north.y, d->p.pos);
	else if (c == 'E')
		rrotatepoint(deg2rad(90), &d->p.north.x, &d->p.north.y, d->p.pos);
	else if (c == 'W')
		rotatepoint(deg2rad(90), &d->p.north.x, &d->p.north.y, d->p.pos);
}

void	initimg2d(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	d->move = 0;
	while (i < d->height)
	{
		j = 0;
		while (j < d->len)
		{
			if (ft_belong(d->map[i][j], "NSEW"))
				init_player(d, i, j, d->map[i][j]);
			j++;
		}
		i++;
	}
}
