/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:30:16 by antbarbi          #+#    #+#             */
/*   Updated: 2022/09/30 12:47:06 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**final_map_alloc(t_data *data)
{
	int		i;
	char	**flood_map;

	i = 0;
	flood_map = malloc(sizeof(char *) * (HEIGHT + 1));
	if (!flood_map)
		return (NULL);
	flood_map[HEIGHT] = NULL;
	while (i < HEIGHT)
	{
		flood_map[i] = malloc(sizeof(char) * (data->len + 1));
		if (!flood_map[i])
			return (NULL);
		flood_map[i][data->len] = '\0';
		i++;
	}
	return (flood_map);
}

void	final_map_assign(t_data *data, char **new_map, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < data->len)
		{
			new_map[i][j] = c;
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	new_map[i] = NULL;
}

void	final_map_insert(t_data *data, char **new_map)
{
	int	i;
	int	j;

	i = 0;
	while (new_map[i])
	{
		j = 0;
		while (new_map[i][j])
		{
			if (data->map[i + 1][j + 1] == ' ')
				new_map[i][j] = '0';
			else
				new_map[i][j] = data->map[i + 1][j + 1];
			j++;
		}
		i++;
	}
}

void	final_map(t_data *data)
{
	char	**new_map;

	new_map = final_map_alloc(data);
	if (!new_map)
		exit_message(data, "Final map alloc failed");
	final_map_assign(data, new_map, '0');
	final_map_insert(data, new_map);
	free_map(data);
	data->map = new_map;
}
