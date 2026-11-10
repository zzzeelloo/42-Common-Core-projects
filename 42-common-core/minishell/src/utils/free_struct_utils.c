/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:35:00 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 18:36:44 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	free_redir_files(t_exec *exec, int i)
{
	if (exec->cmd_redirs[i].infile)
	{
		free(exec->cmd_redirs[i].infile);
		exec->cmd_redirs[i].infile = NULL;
	}
	if (exec->cmd_redirs[i].outfile)
	{
		free(exec->cmd_redirs[i].outfile);
		exec->cmd_redirs[i].outfile = NULL;
	}
	if (exec->cmd_redirs[i].heredoc_delimiter)
	{
		free(exec->cmd_redirs[i].heredoc_delimiter);
		exec->cmd_redirs[i].heredoc_delimiter = NULL;
	}
}

static void	close_redir_fds(t_exec *exec, int i)
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
}

void	free_redir_tables(t_exec *exec)
{
	int	i;

	if (exec->cmd_redirs && exec->total_commands > 0)
	{
		i = 0;
		while (i < exec->total_commands)
		{
			free_redir_files(exec, i);
			close_redir_fds(exec, i);
			i++;
		}
		free(exec->cmd_redirs);
		exec->cmd_redirs = NULL;
	}
}

static void	free_group_commands(char **group)
{
	int	j;

	j = 0;
	while (group[j])
	{
		if (group[j])
		{
			free(group[j]);
			group[j] = NULL;
		}
		j++;
	}
}

void	free_exec_groups(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->groups)
	{
		while (exec->groups[i])
		{
			free_group_commands(exec->groups[i]);
			if (exec->groups[i])
			{
				free(exec->groups[i]);
				exec->groups[i] = NULL;
			}
			i++;
		}
		free(exec->groups);
		exec->groups = NULL;
	}
}
