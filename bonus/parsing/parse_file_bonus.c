/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:54:21 by antbarbi          #+#    #+#             */
/*   Updated: 2022/11/07 09:58:25 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_content(t_data *data, char *line)
{
	static int	i = 0;
	int			chck;

	chck = i;
	if (i == 6)
	{
		if (parse_map(data, line) == -1)
			return (-1);
		return (1);
	}
	if (!data->n_texture)
		i += parse_by_id(&data->n_texture, line, "NO");
	if (!data->s_texture)
		i += parse_by_id(&data->s_texture, line, "SO");
	if (!data->w_texture)
		i += parse_by_id(&data->w_texture, line, "WE");
	if (!data->e_texture)
		i += parse_by_id(&data->e_texture, line, "EA");
	if (!data->f_texture)
		i += parse_color(&data->f_texture, line, 'F');
	if (!data->c_texture)
		i += parse_color(&data->c_texture, line, 'C');
	if (chck == i && line[0] != '\0')
		return (-1);
	return (0);
}

void	check_file_name(t_data *data, char *file)
{
	int	i;

	i = 0;
	if (ft_strlen(file) < 4)
		exit_message(data, "File extension need to be: \".cub\".");
	while (file[i] != '\0')
		i++;
	while (file[i] != '.')
	{
		i--;
		if (i < 0)
			exit_message(data, "File extension need to be: \".cub\".");
	}
	if (ft_strlen(file + i) == 4)
	{
		if (file[i + 1] == 'c' && file[i + 2] == 'u'
			&& file[i + 3] == 'b')
			return ;
		else
			exit_message(data, "File extension need to be: \".cub\".");
	}
	else
		exit_message(data, "File extension need to be: \".cub\".");
}

void	read_cub(t_data *data, char *path_cub)
{
	int			fd;
	int			gnl;
	char		*line_read;
	static int	i = 0;

	gnl = -1;
	line_read = NULL;
	fd = open(path_cub, O_RDONLY | O_NOFOLLOW);
	if (fd == -1)
		exit_message(data, "File does not exist");
	while (gnl != 0)
	{
		gnl = get_next_line(fd, &line_read);
		if (gnl == -1)
			exit_message(data, "Gnl failed");
		if (gnl >= 0)
		{
			if (parse_content(data, line_read) == -1)
				i = -1;
			free(line_read);
		}
	}
	if (i == -1 || !data->map)
		exit_message(data, "Parsing failed file format");
}
