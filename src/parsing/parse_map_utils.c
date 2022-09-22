/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:49:24 by antbarbi          #+#    #+#             */
/*   Updated: 2022/09/22 15:37:39 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_maplen(char **map)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		if ((size_t)max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

int	ft_mapsize(char	**map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	is_forb_elem(char c)
{
	int			i;
	static int	cpt = 0;
	static char	str[] = " 01NSWE";

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W'
				|| str[i] == 'E')
			{
				cpt++;
				if (cpt > 1)
					return (1);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

void	chck_map_elem(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_forb_elem(data->map[i][j]))
				exit_message(data, "Forbidden elem in map found");
			j++;
		}
		i++;
	}
}

int	nb_of_zeros(char **map)
{
	int	j;
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				cpt++;
			j++;
		}
		i++;
	}
	return (cpt);
}

void	print_map(char	**map) //to delete
{
	int i;

	i = 0;
	if (!map)
	{
		ft_putendl_fd("**map error", 2);
		return ;
	}
	while (map[i])
	{
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(" : len is ", 1);
		ft_putnbr_fd(ft_strlen(map[i]), 1);
		ft_putstr_fd(" : ", 1);
		if (i < 10)
			ft_putstr_fd(" ", 1);
		ft_putendl_fd(map[i], 1);
		i++;
	}
}