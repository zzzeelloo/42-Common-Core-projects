/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_0_exec_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:50:00 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/10 19:35:51 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	cleanup_cmd_redirections(t_exec *exec)
{
	int	i;

	if (exec->cmd_redirs && exec->total_commands > 0)
	{
		i = 0;
		while (i < exec->total_commands)
		{
			if (exec->cmd_redirs[i].infile)
				free(exec->cmd_redirs[i].infile);
			if (exec->cmd_redirs[i].outfile)
				free(exec->cmd_redirs[i].outfile);
			if (exec->cmd_redirs[i].heredoc_delimiter)
				free(exec->cmd_redirs[i].heredoc_delimiter);
			i++;
		}
		free(exec->cmd_redirs);
		exec->cmd_redirs = NULL;
	}
}

void	cleanup_child_memory_for_execve(t_exec *exec)
{
	if (exec->pipex.paths)
	{
		ft_freesplit(exec->pipex.paths);
		exec->pipex.paths = NULL;
	}
	if (exec->pipex.pids)
	{
		free(exec->pipex.pids);
		exec->pipex.pids = NULL;
	}
	cleanup_cmd_redirections(exec);
	if (exec->groups)
	{
		free(exec->groups);
		exec->groups = NULL;
	}
}

void	cleanup_child_groups(t_exec *exec)
{
	int	i;
	int	j;

	if (exec->groups)
	{
		i = 0;
		while (exec->groups[i])
		{
			if (exec->groups[i])
			{
				j = 0;
				while (exec->groups[i][j])
				{
					free(exec->groups[i][j]);
					j++;
				}
				free(exec->groups[i]);
			}
			i++;
		}
		free(exec->groups);
		exec->groups = NULL;
	}
}

void	cleanup_child_redirs(t_exec *exec)
{
	int	i;

	if (exec->cmd_redirs && exec->total_commands > 0)
	{
		i = 0;
		while (i < exec->total_commands)
		{
			if (exec->cmd_redirs[i].infile)
				free(exec->cmd_redirs[i].infile);
			if (exec->cmd_redirs[i].outfile)
				free(exec->cmd_redirs[i].outfile);
			if (exec->cmd_redirs[i].heredoc_delimiter)
				free(exec->cmd_redirs[i].heredoc_delimiter);
			i++;
		}
		free(exec->cmd_redirs);
		exec->cmd_redirs = NULL;
	}
}

void	cleanup_child_memory_full(t_exec *exec)
{
	if (exec->pipex.paths)
	{
		ft_freesplit(exec->pipex.paths);
		exec->pipex.paths = NULL;
	}
	if (exec->pipex.pids)
	{
		free(exec->pipex.pids);
		exec->pipex.pids = NULL;
	}
	if (exec->pipex.cmd)
	{
		free(exec->pipex.cmd);
		exec->pipex.cmd = NULL;
	}
	cleanup_child_groups(exec);
	cleanup_child_redirs(exec);
}
