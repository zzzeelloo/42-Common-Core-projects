/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:27:32 by anpetit           #+#    #+#             */
/*   Updated: 2026/02/23 19:27:33 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (game_exit(game, 0));
	if (keycode >= 0 && keycode < 65364)
		game->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65364)
		game->keys[keycode] = 0;
	return (0);
}
