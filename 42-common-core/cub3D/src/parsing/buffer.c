/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:43:02 by anpetit           #+#    #+#             */
/*   Updated: 2026/02/23 21:43:03 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

static int	get_n_lines(char *file)
{
	int		fd;
	int		n_lines;
	char	tmp;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("Map can´t be opened"), -1);
	n_lines = 0;
	while (read(fd, &tmp, sizeof(char)) > 0)
	{
		if (tmp == '\n')
			n_lines++;
	}
	close(fd);
	return (++n_lines);
}

static void	fill_out_buffer(char **buffer, int fd, int buffer_size)
{
	int	i;

	if (!buffer)
		return ;
	i = 0;
	while (i < buffer_size)
	{
		buffer[i] = get_next_line(fd);
		if (!buffer[i])
			break ;
		i++;
	}
	buffer[i] = NULL;
}

static void	drain_gnl(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
}

char	**get_buffer(char *file)
{
	int		fd;
	char	**buffer;
	int		buffer_size;

	buffer_size = get_n_lines(file);
	if (buffer_size == -1)
		return (NULL);
	buffer = (char **)malloc(sizeof(char *) * (buffer_size + 1));
	if (!buffer)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("Map can´t be opened"), free(buffer), NULL);
	fill_out_buffer(buffer, fd, buffer_size);
	drain_gnl(fd);
	close(fd);
	return (buffer);
}
