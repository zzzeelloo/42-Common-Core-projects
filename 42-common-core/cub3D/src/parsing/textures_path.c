/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:32:23 by zcherif           #+#    #+#             */
/*   Updated: 2026/02/23 19:39:19 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

static int	get_path(t_tex *tex, char *line, int i, bool *check)
{
	int	end;

	if (tex->path)
	{
		*check = false;
		return (error("There must be exactly one texture for each wall side"));
	}
	end = ft_strlen(line) - 1;
	while (end > i && (line[end] == '\n' || line[end] == ' '
			|| line[end] == '\t'))
		end--;
	tex->path = ft_substr(line, i, end - i + 1);
	if (!tex->path)
	{
		*check = false;
		return (error("Cannot get texture path"));
	}
	return (0);
}

int	get_tex(char *line, t_game *game)
{
	int		i;
	bool	check;

	if (!line || !game)
		return (1);
	i = 2;
	check = true;
	while (ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(line, "NO", 2))
		get_path(&game->config.no, line, i, &check);
	else if (!ft_strncmp(line, "SO", 2))
		get_path(&game->config.so, line, i, &check);
	else if (!ft_strncmp(line, "WE", 2))
		get_path(&game->config.we, line, i, &check);
	else if (!ft_strncmp(line, "EA", 2))
		get_path(&game->config.ea, line, i, &check);
	if (!check)
		return (1);
	return (0);
}
