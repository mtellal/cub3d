/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:38:26 by antbarbi          #+#    #+#             */
/*   Updated: 2022/09/30 12:58:40 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	chck_path(t_data *data)
{
	int	fd;

	fd = open(data->n_texture, O_RDONLY);
	if (fd == -1)
		exit_message(data, "NO File not found");
	close(fd);
	fd = open(data->s_texture, O_RDONLY);
	if (fd == -1)
		exit_message(data, "SO File not found");
	close(fd);
	fd = open(data->w_texture, O_RDONLY);
	if (fd == -1)
		exit_message(data, "WE File not found");
	close(fd);
	fd = open(data->e_texture, O_RDONLY);
	if (fd == -1)
		exit_message(data, "EA File not found");
	close(fd);
}

void	chck_color(t_data *data, char *str)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			cpt++;
		else if (str[i] == ',')
		{
			if (cpt < 1 || cpt > 3)
				exit_message(data, "Color error");
			cpt = 0;
		}
		else
			exit_message(data, "Color wrong args");
		i++;
	}
	if (cpt < 1 || cpt > 3)
		exit_message(data, "Color error");
}

int	rgb_c(t_data *data, int rgb)
{
	static int	color[3];
	static int	i = 0;
	static int	index = 0;

	color[index] = ft_atoi(data->c_texture);
	while (data->c_texture[i])
	{
		if (data->c_texture[i] == ',')
		{
			index++;
			color[index] = ft_atoi(data->c_texture + i + 1);
		}
		i++;
	}
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		exit_message(data, "Color value not accurate");
	return (color[rgb]);
}

int	rgb_f(t_data *data, int rgb)
{
	static int	color[3];
	static int	i = 0;
	static int	index = 0;

	color[index] = ft_atoi(data->f_texture);
	while (data->f_texture[i])
	{
		if (data->f_texture[i] == ',')
		{
			index++;
			color[index] = ft_atoi(data->f_texture + i + 1);
		}
		i++;
	}
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		exit_message(data, "Color value not accurate");
	if (rgb > 2 || rgb < 0)
		return (0);
	return (color[rgb]);
}

void	chck_textures(t_data *data)
{
	chck_path(data);
	chck_color(data, data->c_texture);
	chck_color(data, data->f_texture);
	rgb_c(data, 2);
	rgb_f(data, 2);
}
