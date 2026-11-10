/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:27:34 by anpetit           #+#    #+#             */
/*   Updated: 2026/02/23 20:42:14 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

static int	is_walkable_cell(t_game *game, int mx, int my)
{
	int		len;
	char	c;

	if (my < 0 || my >= game->config.map->height)
		return (0);
	len = (int)ft_strlen(game->config.map->grid[my]);
	if (mx < 0 || mx >= len)
		return (0);
	c = game->config.map->grid[my][mx];
	if (c == '1' || c == ' ')
		return (0);
	return (1);
}

static int	can_move_to(t_game *game, float x, float y)
{
	float	r;

	r = (float)PLAYER_RADIUS;
	if (!is_walkable_cell(game, (int)((x + r) / TILE_SIZE),
		(int)(y / TILE_SIZE)))
		return (0);
	if (!is_walkable_cell(game, (int)((x - r) / TILE_SIZE),
		(int)(y / TILE_SIZE)))
		return (0);
	if (!is_walkable_cell(game, (int)(x / TILE_SIZE),
		(int)((y + r) / TILE_SIZE)))
		return (0);
	if (!is_walkable_cell(game, (int)(x / TILE_SIZE),
		(int)((y - r) / TILE_SIZE)))
		return (0);
	return (1);
}

void	make_move(t_game *game, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	if (can_move_to(game, new_x, game->player.y))
		game->player.x = new_x;
	if (can_move_to(game, game->player.x, new_y))
		game->player.y = new_y;
}
