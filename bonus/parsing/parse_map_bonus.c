/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:29:59 by antbarbi          #+#    #+#             */
/*   Updated: 2022/09/22 15:35:33 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**map_realloc(t_data *data, char *line)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = malloc(sizeof(char *) * (ft_mapsize(data->map) + 2));
	if (!tmp)
		exit_message(data, "map realoc failed");
	while (data->map[++i])
		tmp[i] = ft_strdup(data->map[i]);
	if (line)
		tmp[i] = ft_strdup(line);
	tmp[i + 1] = NULL;
	free_map(data);
	return (tmp);
}

void	parse_rough_map(t_data *data, char *line)
{
	if (!data->map)
	{
		data->map = malloc(sizeof(char *) * 2);
		if (!data->map)
			exit_message(data, "map alloc failed");
		data->map[0] = ft_strdup(line);
		if (!data->map[0])
			exit_message(data, "map[0] alloc failed");
		data->map[1] = NULL;
	}
	else
		data->map = map_realloc(data, line);
	data->height = ft_mapsize(data->map);
	data->len = ft_maplen(data->map);
}

int	check_is_map(char *line)
{
	static int	map_exist = 0;
	static int	map_end = 0;

	if (line[0] != '\0')
	{
		if (map_end)
			return (-1);
		map_exist = 1;
		return (1);
	}
	if (map_exist)
		map_end = 1;
	return (0);
}

int	parse_map(t_data *data, char *line)
{
	if (check_is_map(line) == -1)
		return (-1);
	if (check_is_map(line) == 1)
		parse_rough_map(data, line);
	return (1);
}
