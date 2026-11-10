/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_2_group_finalization.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:37:21 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:37:21 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	finalize_group(t_exec *exec)
{
	int	i;

	if (!exec->ncmd)
	{
		exec->group = malloc(sizeof(char *));
		if (exec->group)
			exec->group[0] = NULL;
		return ;
	}
	exec->group = malloc((exec->ncmd + 1) * sizeof(char *));
	if (!exec->group)
		return ;
	i = 0;
	while (i < exec->ncmd)
	{
		exec->group[i] = exec->cmds[i];
		exec->cmds[i] = NULL;
		i++;
	}
	exec->group[exec->ncmd] = NULL;
}
