/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:31:00 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 18:31:00 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	free_exec_core(t_exec *exec)
{
	free_exec_groups(exec);
	free_redir_tables(exec);
}

static void	free_pipex_core(t_exec *exec)
{
	if (!exec)
		return ;
	free_exec_core(exec);
	cleanup_pipex_complete(exec);
}

void	free_pipex_no_exit(t_exec *exec, int status, char *str, char *str2)
{
	if (!exec)
	{
		if (status != -1)
			g_exit_status = status;
		return ;
	}
	if (str || str2)
	{
		ft_message(str, str2);
		ft_putstr_fd("\n", 2);
	}
	free_pipex_core(exec);
	if (status != -1)
		g_exit_status = status;
}

void	free_pipex(t_exec *exec, int status, char *str, char *str2)
{
	free_pipex_no_exit(exec, status, str, str2);
	if (status != -1)
		exit(status);
}

void	free_exec(t_exec *exec, int status, char *str, char *str2)
{
	if (!exec)
	{
		if (status != -1)
			g_exit_status = status;
		return ;
	}
	if (str || str2)
		ft_message(str, str2);
	free_exec_core(exec);
	free_pipex_resources(exec);
	if (status != -1)
		g_exit_status = status;
}
