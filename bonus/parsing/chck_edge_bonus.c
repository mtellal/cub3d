/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_edge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:10:58 by antbarbi          #+#    #+#             */
/*   Updated: 2022/11/08 16:47:17 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**floodable_map_alloc(t_data *data)
{
	int		i;
	char	**flood_map;

	i = 0;
	flood_map = malloc(sizeof(char *) * (HEIGHT + 3));
	if (!flood_map)
		return (NULL);
	flood_map[HEIGHT + 2] = NULL;
	while (i < HEIGHT + 2)
	{
		flood_map[i] = malloc(sizeof(char) * (data->len + 3));
		if (!flood_map[i])
			return (NULL);
		flood_map[i][data->len + 2] = '\0';
		i++;
	}
	return (flood_map);
}

void	floodable_map_assign(t_data *data, char **new_map, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT + 2)
	{
		j = 0;
		while (j < data->len + 2)
		{
			new_map[i][j] = c;
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	new_map[i] = NULL;
}

void	map_insert(t_data *data, char **new_map, char replacement)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				new_map[i + 1][j + 1] = replacement;
			else
				new_map[i + 1][j + 1] = data->map[i][j];
			j++;
		}
		i++;
	}
}

int	map_check_zero(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i] && map[i + 1])
	{
		j = 1;
		while (map[i][j] && map[i][j + 1])
		{
			if (map[i][j] == '0'
				&& (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
				|| map[i][j - 1] == ' ' || map[i][j + 1] == ' '))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	chck_map_edges(t_data *data)
{
	char	**new_map;

	new_map = floodable_map_alloc(data);
	if (!new_map)
		exit_message(data, "new/tmp_map alloc failed");
	floodable_map_assign(data, new_map, ' ');
	map_insert(data, new_map, ' ');
	stock_player_and_replace(new_map);
	free_map(data);
	data->map = new_map;
	if (map_check_zero(data->map)
		|| stock_player_and_replace(data->map))
		exit_message(data, "Map is not closed");
}
