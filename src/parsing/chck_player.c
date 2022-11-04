/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:18:26 by antbarbi          #+#    #+#             */
/*   Updated: 2022/11/04 15:56:27 by antbarbi         ###   ########.fr       */
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

int	stock_player_and_replace(char **map)
{
	static int	y = 0;
	static int	x = 0;
	static char	c;

	if (y || x)
	{
		if (map[y][x] == ' ')
			return (1);
		map[y][x] = c;
		return (0);
	}
	while (map[y++])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]))
			{
				c = map[y][x];
				map[y][x] = '0';
			}
			x++;
		}
	}
	return (0);
}

int	compare_maps(char **map, char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != tab[i][j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
