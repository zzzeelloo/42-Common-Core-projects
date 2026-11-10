/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:27:20 by anpetit           #+#    #+#             */
/*   Updated: 2026/02/23 20:44:49 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

static double	get_angle(t_game *game, int x)
{
	double	initial_fov_angle;
	double	proportion_of_screen;
	double	where_in_fov;

	initial_fov_angle = game->config.player_angle - (game->config.fov / 2);
	proportion_of_screen = (double)x / (double)(WIDTH - 1);
	where_in_fov = proportion_of_screen * game->config.fov;
	return (initial_fov_angle + where_in_fov);
}

static double	get_height_wall(double raw_dist, double ray_angle, t_game *game)
{
	double	dist_corrected;
	double	plane_dist;
	double	wall_height;

	dist_corrected = raw_dist * cos(ray_angle - game->config.player_angle);
	if (dist_corrected < 0.00001)
		dist_corrected = 0.00001;
	plane_dist = (WIDTH / 2.0) / tan(game->config.fov / 2.0);
	wall_height = (1.0 / dist_corrected) * plane_dist;
	return (wall_height);
}

static double	get_dist_hit_raw(t_game *game, t_dda *dda)
{
	double	dist_hit;
	double	pos_x;
	double	pos_y;

	pos_x = game->player.x / (double)TILE_SIZE;
	pos_y = game->player.y / (double)TILE_SIZE;
	if (dda->side == 0)
		dist_hit = (dda->map_x - pos_x
				+ (1 - dda->step_x) / 2) / dda->ray_dir_x;
	else
		dist_hit = (dda->map_y - pos_y
				+ (1 - dda->step_y) / 2) / dda->ray_dir_y;
	return (dist_hit);
}

void	render_walls(t_game *game)
{
	int		x;
	double	ray_angle;
	t_dda	dda;
	double	wall_height;

	x = 0;
	while (x < WIDTH)
	{
		ray_angle = get_angle(game, x);
		run_dda(game, ray_angle, &dda);
		dda.raw_dist = get_dist_hit_raw(game, &dda);
		wall_height = get_height_wall(dda.raw_dist, ray_angle, game);
		draw_wall_column_texturized(game, x, wall_height, &dda);
		x++;
	}
}
