/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:18:26 by antbarbi          #+#    #+#             */
/*   Updated: 2022/11/04 15:45:39 by antbarbi         ###   ########.fr       */
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

void	stock_player_and_replace(t_data *data, char **map)
{
	static int	y = 0;
	static int	x = 0;
	static char	c;

	if (y || x)
	{
		if (map[y][x] == ' ')
			exit_message(data, "Player out of bound");
		map[y][x] = c;
		return ;
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
				return ;
			}
			x++;
		}
	}
}
