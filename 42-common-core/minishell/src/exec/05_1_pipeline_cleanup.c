/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_1_pipeline_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:36:03 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:36:59 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

void	cleanup_parent_fds(t_exec *exec, int group_count)
{
	int	i;

	if (!exec || !exec->cmd_redirs)
		return ;
	i = 0;
	while (i < group_count)
	{
		if (exec->cmd_redirs[i].infile_fd != -1)
		{
			close(exec->cmd_redirs[i].infile_fd);
			exec->cmd_redirs[i].infile_fd = -1;
		}
		if (exec->cmd_redirs[i].outfile_fd != -1)
		{
			close(exec->cmd_redirs[i].outfile_fd);
			exec->cmd_redirs[i].outfile_fd = -1;
		}
		if (exec->cmd_redirs[i].is_heredoc
			&& exec->cmd_redirs[i].heredoc_fd != -1)
		{
			close(exec->cmd_redirs[i].heredoc_fd);
			exec->cmd_redirs[i].heredoc_fd = -1;
		}
		i++;
	}
}

void	cleanup_pipes_on_error(int *pipe_fd, int prev_pipe_read,
		int pipe_created)
{
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	if (pipe_created)
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
	}
}

void	cleanup_created_processes(t_exec *exec, int up_to_index)
{
	int	j;

	j = 0;
	while (j < up_to_index)
	{
		if (exec->pipex.pids[j] > 0)
		{
			kill(exec->pipex.pids[j], SIGTERM);
			waitpid(exec->pipex.pids[j], NULL, 0);
		}
		j++;
	}
}

void	handle_pipe_creation_error(t_exec *exec, int i, int prev_pipe_read)
{
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	cleanup_created_processes(exec, i);
	cleanup_parent_fds(exec, i);
}

void	finalize_pipeline(t_exec *exec, int group_count)
{
	int	i;
	int	status;

	signal(SIGINT, SIG_IGN);
	i = 0;
	while (i < group_count)
	{
		waitpid(exec->pipex.pids[i], &status, 0);
		if (i == group_count - 1)
		{
			if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
			else if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
		}
		i++;
	}
	signals_monitoring();
	cleanup_all_heredocs(exec);
	cleanup_parent_fds(exec, group_count);
	free(exec->pipex.pids);
	exec->pipex.pids = NULL;
	ft_freesplit(exec->pipex.paths);
	exec->pipex.paths = NULL;
}
