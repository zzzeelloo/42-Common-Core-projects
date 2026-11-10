/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_1_pipeline_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:57:49 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 19:08:41 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

int	initialize_pipeline(t_exec *exec, int group_count, char **envp)
{
	pipex_init(exec, envp);
	exec->pipex.cmd_nbr = group_count;
	exec->pipex.pids = malloc(sizeof(pid_t) * group_count);
	if (!exec->pipex.pids)
	{
		perror("malloc");
		if (exec->pipex.paths)
		{
			ft_freesplit(exec->pipex.paths);
			exec->pipex.paths = NULL;
		}
		return (-1);
	}
	return (0);
}

void	setup_pipe_first_descriptors(t_exec *exec, int *pipe_fd,
		int group_count, int i)
{
	exec->pipex.fd[0] = -1;
	if (i < group_count - 1)
		exec->pipex.fd[1] = pipe_fd[1];
	else
		exec->pipex.fd[1] = -1;
}

void	setup_pipe_last_descriptors(t_exec *exec, int prev_pipe_read)
{
	exec->pipex.fd[0] = prev_pipe_read;
	exec->pipex.fd[1] = -1;
}

void	setup_pipe_middle_descriptors(t_exec *exec, int prev_pipe_read,
		int *pipe_fd)
{
	exec->pipex.fd[0] = prev_pipe_read;
	exec->pipex.fd[1] = pipe_fd[1];
}

void	setup_pipe_descriptors(t_exec *exec, int group_count,
		int prev_pipe_read, int *pipe_fd)
{
	if (exec->pipex.i == 0)
		setup_pipe_first_descriptors(exec, pipe_fd, group_count, exec->pipex.i);
	else if (exec->pipex.i == group_count - 1)
		setup_pipe_last_descriptors(exec, prev_pipe_read);
	else
		setup_pipe_middle_descriptors(exec, prev_pipe_read, pipe_fd);
}
