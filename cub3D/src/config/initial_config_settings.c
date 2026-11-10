/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_config_settings.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:27:52 by anpetit           #+#    #+#             */
/*   Updated: 2026/02/23 19:27:53 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

void	init_tex(t_tex *tex)
{
	tex->path = NULL;
	tex->img = NULL;
	tex->addr = NULL;
	tex->bpp = 0;
	tex->endian = 0;
	tex->height = 0;
	tex->line_len = 0;
	tex->width = 0;
	tex->num = 0;
}

void	init_config(t_config *config)
{
	init_tex(&config->no);
	init_tex(&config->so);
	init_tex(&config->we);
	init_tex(&config->ea);
	config->floor_color = 0;
	config->floor_color_found = false;
	config->ceil_color = 0;
	config->ceil_color_found = false;
	config->fov = PI / 3;
	config->player_angle = 0;
	config->map = NULL;
}
