/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:32:17 by zcherif           #+#    #+#             */
/*   Updated: 2026/02/23 19:32:20 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

static int	load_texture(t_game *game, t_tex *tex, char *path)
{
	if (!game->mlx || !path)
		return (error("Cannot load textures"));
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
		return (error("IMG cannot be created"));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (error("ADDR cannot be created"));
	return (0);
}

int	init_textures(t_game *game)
{
	if (load_texture(game, &game->config.no, game->config.no.path))
		return (1);
	if (load_texture(game, &game->config.so, game->config.so.path))
		return (1);
	if (load_texture(game, &game->config.we, game->config.we.path))
		return (1);
	if (load_texture(game, &game->config.ea, game->config.ea.path))
		return (1);
	return (0);
}
