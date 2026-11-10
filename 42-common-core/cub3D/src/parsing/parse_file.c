/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:31:49 by zcherif           #+#    #+#             */
/*   Updated: 2026/02/23 20:13:28 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

static int	parse_identifier(char *line, t_game *game)
{
	if (*line == '\n' || *line == '\0')
		return (0);
	else if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		if (get_tex(line, game))
			return (1);
	}
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		if (get_color(line, game))
			return (1);
	}
	else
		return (error("Unexpected line: file must contain "
				"4 textures, 2 colors and a map"));
	return (0);
}

static int	parse_textures(char **lines, t_game *game, int *map_index)
{
	int	i;

	i = -1;
	while (lines[++i] && !all_textures_found(game))
	{
		if (parse_identifier(skip_spaces(lines[i]), game))
			return (1);
	}
	if (!all_textures_found(game))
		return (error("Missing textures or colors"));
	if (find_map(lines, i, map_index))
		return (1);
	return (0);
}

int	parse_file(char *file, t_game *game)
{
	char	**buffer;
	int		map_index;

	buffer = get_buffer(file);
	if (!buffer)
		return (1);
	if (parse_textures(buffer, game, &map_index))
	{
		free_array(buffer);
		return (1);
	}
	if (parse_map(buffer, game, map_index))
	{
		free_array(buffer);
		return (1);
	}
	free_array(buffer);
	if (get_player_data(game))
		return (1);
	return (0);
}
