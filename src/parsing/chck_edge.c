/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_edge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:10:58 by antbarbi          #+#    #+#             */
/*   Updated: 2022/11/05 11:19:44 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**floodable_map_alloc(t_data *data)
{
	int		i;
	char	**flood_map;

	i = 0;
	flood_map = malloc(sizeof(char *) * (data->height + 3));
	if (!flood_map)
		return (NULL);
	flood_map[data->height + 2] = NULL;
	while (i < data->height + 2)
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
	while (i < data->height + 2)
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

void	flood_algo(char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= ft_maplen(map)
		|| y >= ft_mapsize(map) || map[y][x] != '0')
		return ;
	map[y][x] = ' ';
	flood_algo(map, x + 1, y);
	flood_algo(map, x - 1, y);
	flood_algo(map, x, y + 1);
	flood_algo(map, x, y - 1);
	return ;
}

void	chck_map_edges(t_data *data)
{
	char	**new_map;
	char	**tmp_map;
	int		cpt_zeros;

	cpt_zeros = nb_of_zeros(data->map, '0');
	new_map = floodable_map_alloc(data);
	tmp_map = floodable_map_alloc(data);
	if (!new_map || !tmp_map)
		exit_message(data, "new/tmp_map alloc failed");
	floodable_map_assign(data, new_map, '0');
	floodable_map_assign(data, tmp_map, ' ');
	map_insert(data, new_map, '0');
	map_insert(data, tmp_map, ' ');
	stock_player_and_replace(new_map);
	flood_algo(new_map, 0, 0);
	free_map(data);
	data->map = new_map;
	if (stock_player_and_replace(data->map)
		|| cpt_zeros != nb_of_zeros(data->map, '0')
		|| compare_maps(data->map, tmp_map))
	{
		free_tabs(tmp_map);
		exit_message(data, "Map is not closed");
	}
	free_tabs(tmp_map);
}
