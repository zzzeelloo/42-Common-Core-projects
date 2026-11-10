/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:58:49 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	cleanup_all_open_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

static void	cleanup_single_cmd_redir(t_cmd_redir *cmd_redir)
{
	if (cmd_redir->infile_fd != -1)
	{
		close(cmd_redir->infile_fd);
		cmd_redir->infile_fd = -1;
	}
	if (cmd_redir->outfile_fd != -1)
	{
		close(cmd_redir->outfile_fd);
		cmd_redir->outfile_fd = -1;
	}
	if (cmd_redir->is_heredoc && cmd_redir->heredoc_fd != -1)
	{
		close(cmd_redir->heredoc_fd);
		cmd_redir->heredoc_fd = -1;
	}
}

static void	cleanup_cmd_redirs(t_exec *exec)
{
	int	i;

	if (!exec->cmd_redirs)
		return ;
	i = 0;
	while (i < exec->total_commands)
	{
		cleanup_single_cmd_redir(&exec->cmd_redirs[i]);
		i++;
	}
}

static void	cleanup_pipex_fds(t_exec *exec)
{
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
}

void	cleanup_exec_fds(t_exec *exec)
{
	if (!exec)
		return ;
	cleanup_cmd_redirs(exec);
	cleanup_pipex_fds(exec);
}
