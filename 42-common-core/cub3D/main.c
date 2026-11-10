/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:04:45 by anpetit           #+#    #+#             */
/*   Updated: 2026/02/23 21:04:47 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/src.h"

static int	is_cub(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len <= 4)
		return (0);
	if (arg[len - 4] == '.' && arg[len - 3] == 'c' && arg[len - 2] == 'u'
		&& arg[len - 1] == 'b')
		return (1);
	return (0);
}

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error("MLX can't be created"), free_game(game, 1));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		return (error("WIN can't be created"), free_game(game, 1));
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		return (error("IMG can't be created"), free_game(game, 1));
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	if (!game->img.addr)
		return (error("IMG data can't be retrieved"), free_game(game, 1));
	return (0);
}

static void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, render_frame, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error("Usage: ./cub3D <map.cub>"));
	if (!is_cub(argv[1]))
		return (error("Map must have .cub format"));
	init_game(&game);
	if (parse_file(argv[1], &game))
		return (free_game(&game, 1));
	if (init_mlx(&game) != 0)
		return (1);
	if (init_textures(&game))
		return (free_game(&game, 1));
	init_hooks(&game);
	mlx_loop(game.mlx);
	return (free_game(&game, 0));
}
