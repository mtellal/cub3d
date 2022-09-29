/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:38:26 by antbarbi          #+#    #+#             */
/*   Updated: 2022/09/29 17:28:57 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	chck_path(t_data *data)
{
	if (open(data->n_texture, O_RDONLY) == -1)
		exit_message(data, "NO File not found");
	if (open(data->s_texture, O_RDONLY) == -1)
		exit_message(data, "SO File not found");
	if (open(data->w_texture, O_RDONLY) == -1)
		exit_message(data, "WE File not found");
	if (open(data->e_texture, O_RDONLY) == -1)
		exit_message(data, "EA File not found");
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

void	chck_textures(t_data *data)
{
	chck_path(data);
	chck_color(data, data->c_texture);
	chck_color(data, data->f_texture);
}