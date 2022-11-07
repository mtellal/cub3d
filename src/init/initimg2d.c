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

void	fillimg2d(t_data *d, t_frame *im)
{
	int	i;
	int	j;

	i = 0;
	while (i < im->height / GRID)
	{
		j = 0;
		while (j < im->width / GRID)
		{
			if (ft_belong(d->map[i][j], "NSEW"))
				inittriangle(im, i, j, d->map[i][j]);
			j++;
		}
		i++;
	}
}

void	initimg2d(t_data *d, t_frame *i)
{
	i->img = mlx_new_image(d->mlx, i->width, i->height);
	if (!i->img)
		exit_cub(d, "Mlx new image failed");
	i->addr = mlx_get_data_addr(i->img, &i->bpp, &i->length, &i->endian);
	if (!i->addr)
		exit_cub(d, "Mlx get adrr img2D failed");
	i->move = 0;
	fillimg2d(d, i);
}
