/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:18:26 by antbarbi          #+#    #+#             */
/*   Updated: 2022/09/23 14:25:20 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stock_player_and_replace(char **map)
{
	static int	y = 0;
	static int	x = 0;
	static char	c;

	if (y || x)
	{
		map[y][x] = c;
		return ;
	}
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
			{
				c = map[y][x];
				map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}