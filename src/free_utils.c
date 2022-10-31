/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:41:03 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 14:35:45 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rays(t_ray **rays, int l)
{
	int	i;

	i = 0;
	while (i < l)
	{
		free(rays[i]);
		i++;
	}
	free(rays);
}

void	free_tabs(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		free(s[i++]);
	if (s)
		free(s);
}

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			if (data->map[i])
			{
				free(data->map[i]);
				data->map[i] = NULL;
			}
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
}

void	free_texture(t_data *data)
{
	if (data->n_texture)
		free(data->n_texture);
	if (data->s_texture)
		free(data->s_texture);
	if (data->w_texture)
		free(data->w_texture);
	if (data->e_texture)
		free(data->e_texture);
	if (data->c_texture)
		free(data->c_texture);
	if (data->f_texture)
		free(data->f_texture);
}

void	exit_message(t_data *data, char *str)
{
	ft_putendl_fd("Error", 2);
	if (str)
		ft_putendl_fd(str, 2);
	free_texture(data);
	free_map(data);
	if (data->mlx)
		free(data->mlx);
	exit(1);
}
