/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_3_pipeline_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:26:14 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 18:48:59 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

int	create_child_process(t_exec *exec, int i, char **envp)
{
	exec->pipex.pids[i] = fork();
	if (exec->pipex.pids[i] == -1)
	{
		perror("fork");
		if (exec->pipex.fd[0] != -1)
		{
			close(exec->pipex.fd[0]);
			exec->pipex.fd[0] = -1;
		}
		if (exec->pipex.fd[1] != -1)
		{
			close(exec->pipex.fd[1]);
			exec->pipex.fd[1] = -1;
		}
		return (-1);
	}
	if (exec->pipex.pids[i] == 0)
	{
		setup_redirections(exec);
		execute_bonus_args(exec, exec->groups[i], envp);
		exit(0);
	}
	return (0);
}

int	process_single_command(t_exec *exec, char **envp)
{
	setup_pipe_descriptors(exec, exec->pipex.cmd_nbr,
		exec->pipex.prev_pipe_read, exec->pipex.pipe_fd);
	if (create_child_process(exec, exec->pipex.i, envp) == -1)
	{
		cleanup_pipes_on_error(exec->pipex.pipe_fd,
			exec->pipex.prev_pipe_read, 1);
		cleanup_created_processes(exec, exec->pipex.i);
		cleanup_parent_fds(exec, exec->pipex.i);
		return (-1);
	}
	return (0);
}

int	setup_pipeline_context(t_exec *exec, int i, int group_count,
		int prev_pipe_read)
{
	exec->pipex.i = i;
	exec->pipex.cmd_nbr = group_count;
	exec->pipex.prev_pipe_read = prev_pipe_read;
	return (0);
}

int	process_pipeline_command(t_exec *exec, int i, int group_count, char **envp)
{
	int	pipe_fd[2];
	int	pipe_created;

	setup_pipeline_context(exec, i, group_count, exec->pipex.prev_pipe_read);
	pipe_created = 0;
	if (create_pipe_for_command(i, group_count, pipe_fd, &pipe_created) == -1)
	{
		handle_pipe_creation_error(exec, i, exec->pipex.prev_pipe_read);
		return (-1);
	}
	exec->pipex.pipe_fd[0] = pipe_fd[0];
	exec->pipex.pipe_fd[1] = pipe_fd[1];
	if (process_single_command(exec, envp) == -1)
		return (-1);
	exec->pipex.prev_pipe_read = handle_parent_pipes
		(exec->pipex.prev_pipe_read, i, group_count, pipe_fd);
	return (0);
}

int	execute_pipeline_commands(t_exec *exec, int group_count, char **envp)
{
	int	i;

	i = 0;
	exec->pipex.prev_pipe_read = -1;
	while (i < group_count)
	{
		if (process_pipeline_command(exec, i, group_count, envp) == -1)
			return (-1);
		i++;
	}
	cleanup_parent_fds(exec, group_count);
	return (0);
}
