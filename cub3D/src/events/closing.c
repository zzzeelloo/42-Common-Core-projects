/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:27:28 by anpetit           #+#    #+#             */
/*   Updated: 2026/02/23 19:27:29 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/src.h"

int	game_exit(t_game *game, int status)
{
	free_game(game, 0);
	exit(status);
	return (0);
}

int	close_window(t_game *game)
{
	return (game_exit(game, 0));
}
