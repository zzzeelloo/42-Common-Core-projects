/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:47:28 by zcherif           #+#    #+#             */
/*   Updated: 2026/02/23 20:14:40 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!(line[i] == '1' || line[i] == '0' || line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
				|| line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

bool	all_textures_found(t_game *game)
{
	if (game->config.no.path && game->config.so.path && game->config.we.path
		&& game->config.ea.path && game->config.floor_color_found
		&& game->config.ceil_color_found)
		return (1);
	return (0);
}

int	find_map(char **lines, int i, int *map_index)
{
	i--;
	while (lines[++i])
	{
		if (!ft_strcmp(lines[i], "\n"))
			continue ;
		else if (is_map_line(lines[i]))
			break ;
		else
			return (error("Unexpected line: file must contain "
					"4 textures, 2 colors and a map"));
	}
	*map_index = i;
	return (0);
}
