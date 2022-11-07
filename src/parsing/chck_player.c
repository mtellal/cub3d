/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:18:26 by antbarbi          #+#    #+#             */
/*   Updated: 2022/11/07 15:26:15 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	place_player(char **map, int x, int y, char c)
{
	if (map[y][x] == ' ')
		return (1);
	map[y][x] = c;
	return (0);
}

int	stock_player_and_replace(char **map)
{
	static int	y = 0;
	static int	x = 0;
	static char	c;

	if (y || x)
		return (place_player(map, x, y, c));
	while (map[y++])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]))
			{
				c = map[y][x];
				map[y][x] = '0';
				return (0);
			}
			x++;
		}
	}
	return (0);
}
