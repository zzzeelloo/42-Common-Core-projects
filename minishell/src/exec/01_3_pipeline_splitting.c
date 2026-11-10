/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_3_pipeline_splitting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:21:00 by zcherif           #+#    #+#             */
/*   Updated: 2025/08/04 09:21:00 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	redirections_and_tokens(t_exec *exec, char **tokens)
{
	int		pipe_count;

	pipe_count = count_pipes(tokens);
	count_redirections(exec, tokens);
	exec->total_commands = pipe_count + 1;
}

static void	init_single_cmd_redir(t_cmd_redir *cmd_redir)
{
	cmd_redir->infile = NULL;
	cmd_redir->outfile = NULL;
	cmd_redir->append = 0;
	cmd_redir->infile_fd = -1;
	cmd_redir->outfile_fd = -1;
	cmd_redir->heredoc_delimiter = NULL;
	cmd_redir->heredoc_fd = -1;
	cmd_redir->is_heredoc = 0;
}

static void	init_cmd_redirections(t_exec *exec, int total_commands)
{
	int	i;

	exec->cmd_redirs = malloc(total_commands * sizeof(t_cmd_redir));
	if (!exec->cmd_redirs)
		return ;
	i = 0;
	while (i < total_commands)
	{
		init_single_cmd_redir(&exec->cmd_redirs[i]);
		i++;
	}
	exec->total_commands = total_commands;
}

static void	finalize_last_group(t_exec *exec)
{
	if (exec->ncmd > 0)
	{
		finalize_group(exec);
		if (exec->group)
		{
			exec->groups[exec->ng] = exec->group;
			exec->ng = exec->ng + 1;
		}
	}
	exec->groups[exec->ng] = NULL;
}

void	split_pipeline_groups(t_exec *exec, char **tokens)
{
	init_exec(exec);
	redirections_and_tokens(exec, tokens);
	init_cmd_redirections(exec, exec->total_commands);
	if (!exec->cmd_redirs)
		return ;
	exec->groups = allocate_groups(exec->count);
	if (!exec->groups)
		free_exec(exec, 1, "Error malloc <split_pipeline_groups>", NULL);
	exec->cmds = allocate_double(exec->count);
	if (!exec->cmds)
		free_exec(exec, 1, "Error malloc <split_pipeline_groups>", NULL);
	split_groups(exec, tokens);
	finalize_last_group(exec);
	free(exec->cmds);
	exec->cmds = NULL;
}
