/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_4_pipeline_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:32:50 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 17:53:11 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

void	handle_pipeline(t_exec *exec, int group_count, char ***env_ptr)
{
	if (initialize_pipeline(exec, group_count, *env_ptr) == -1)
	{
		return ;
	}
	if (execute_pipeline_commands(exec, group_count, *env_ptr) == -1)
	{
		if (exec->pipex.pids)
		{
			free(exec->pipex.pids);
			exec->pipex.pids = NULL;
		}
		if (exec->pipex.paths)
		{
			ft_freesplit(exec->pipex.paths);
			exec->pipex.paths = NULL;
		}
		return ;
	}
	finalize_pipeline(exec, group_count);
	cleanup_exec_fds(exec);
}
