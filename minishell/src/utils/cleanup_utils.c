/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:36:00 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 18:39:52 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	close_pipex_fds(t_exec *exec)
{
	if (exec->pipex.infile >= 0)
		close(exec->pipex.infile);
	if (exec->pipex.outfile >= 0)
		close(exec->pipex.outfile);
	if (exec->pipex.fd[0] >= 0)
		close(exec->pipex.fd[0]);
	if (exec->pipex.fd[1] >= 0)
		close(exec->pipex.fd[1]);
	exec->pipex.fd[0] = -1;
	exec->pipex.fd[1] = -1;
}

static void	cleanup_heredoc_file(t_exec *exec)
{
	if (exec->pipex.here_doc == 1 && exec->pipex.infile_name)
	{
		unlink(exec->pipex.infile_name);
		free(exec->pipex.infile_name);
		exec->pipex.infile_name = NULL;
	}
}

void	free_pipex_resources(t_exec *exec)
{
	if (exec->pipex.paths)
	{
		ft_freesplit(exec->pipex.paths);
		exec->pipex.paths = NULL;
	}
	if (exec->pipex.cmd)
	{
		free(exec->pipex.cmd);
		exec->pipex.cmd = NULL;
	}
	if (exec->pipex.pids)
	{
		free(exec->pipex.pids);
		exec->pipex.pids = NULL;
	}
	if (exec->pipex.cmd_args)
	{
		ft_freesplit(exec->pipex.cmd_args);
		exec->pipex.cmd_args = NULL;
	}
}

void	cleanup_pipex_complete(t_exec *exec)
{
	free_pipex_resources(exec);
	close_pipex_fds(exec);
	cleanup_heredoc_file(exec);
}

void	cleanup_global_resources(t_exec *exec)
{
	if (!exec)
		return ;
	cleanup_all_open_fds();
	free_exec_groups(exec);
	free_redir_tables(exec);
	free_pipex_resources(exec);
	close_pipex_fds(exec);
	cleanup_heredoc_file(exec);
}
