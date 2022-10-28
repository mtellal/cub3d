/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:02:51 by antbarbi          #+#    #+#             */
/*   Updated: 2021/10/30 03:25:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	cut(char **stock)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *stock;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	*stock = ft_substr(tmp, i, ft_strlen(tmp));
	if (!(*stock))
		return (-1);
	free(tmp);
	return (0);
}

static int	readbuff(int fd, char *buff, char **stock)
{
	char	*tmp;
	int		rd;

	rd = read(fd, buff, BUFFER_SIZE);
	while ((rd))
	{
		buff[rd] = '\0';
		tmp = *stock;
		*stock = ft_strjoin(tmp, buff);
		if (!(*stock))
			return (-1);
		free(tmp);
		if (ft_strnchr(buff, '\n', BUFFER_SIZE))
			break ;
		rd = read(fd, buff, BUFFER_SIZE);
	}
	return (rd);
}

void	for_norme(char *stock)
{
	free(stock);
	stock = NULL;
}

int	get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*stock;
	int				rd;

	if (read(fd, NULL, 0) < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!stock)
	{
		stock = malloc(sizeof(char));
		if (!(stock))
			return (-1);
		stock[0] = '\0';
	}
	rd = readbuff(fd, buff, &stock);
	if ((rd) == -1)
		return (-1);
	*line = ft_strndup(stock);
	if (!ft_strnchr(stock, '\n', ft_strlen(stock)))
	{
		for_norme(stock);
		return (0);
	}
	if (cut(&stock) == -1)
		return (-1);
	return (1);
}
