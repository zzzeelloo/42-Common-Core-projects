/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_alg3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:15:19 by zcherif           #+#    #+#             */
/*   Updated: 2024/01/28 17:47:01 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	alg_3(t_s **s_a)
{
	while (s_a != NULL && s_order(*s_a) != 1)
	{
		if ((*s_a)->idx == find_lowest(*s_a))
		{
			swap_a(s_a);
			rot_a(s_a);
		}
		else if ((*s_a)->idx == find_highest(*s_a))
			rot_a(s_a);
		else if ((*s_a)->idx != find_highest(*s_a)
			&& (*s_a)->nxt->idx == find_highest(*s_a))
			rev_rot_a(s_a);
		else
			swap_a(s_a);
	}
}
