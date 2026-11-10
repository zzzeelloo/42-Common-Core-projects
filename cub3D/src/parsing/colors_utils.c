/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:35:04 by zcherif           #+#    #+#             */
/*   Updated: 2026/02/23 20:35:58 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

bool	valid_range(int color[3])
{
	if (color[0] >= 0 && color[0] <= 255 && color[1] >= 0 && color[1] <= 255
		&& color[2] >= 0 && color[2] <= 255)
		return (1);
	return (0);
}

bool	valid_chars(char *line, int color_index)
{
	while (line[color_index])
	{
		if (!ft_isdigit(line[color_index]) && line[color_index] != ','
			&& !ft_isspace(line[color_index]))
			return (0);
		color_index++;
	}
	return (1);
}
