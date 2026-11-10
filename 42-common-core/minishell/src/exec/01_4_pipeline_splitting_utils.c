/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_4_pipeline_splitting_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:21:05 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:22:48 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	**allocate_double(int count)
{
	return (ft_calloc((count + 1), sizeof(char *)));
}

char	***allocate_groups(int count)
{
	return (ft_calloc((count + 1), sizeof(char **)));
}

void	init_exec(t_exec *exec)
{
	exec->count = 0;
	exec->i = 0;
	exec->ncmd = 0;
	exec->ng = 0;
	exec->redir = 0;
	exec->redir_in = 0;
	exec->redir_out = 0;
	exec->current_redir_in = 0;
	exec->current_redir_out = 0;
	exec->group = NULL;
	exec->groups = NULL;
	exec->infile_name = NULL;
	exec->outfile_name = NULL;
	exec->infile = -1;
	exec->outfile = -1;
}

void	count_redirections(t_exec *exec, char **tokens)
{
	while (tokens && tokens[exec->count])
	{
		if (tokens && tokens[exec->count][0] == '<'
			&& tokens[exec->count][1] == '\0')
			exec->redir_in++;
		if ((tokens && tokens[exec->count][0] == '>'
			&& tokens[exec->count][1] == '\0') || (tokens
			&& tokens[exec->count][0] == '>'
			&& tokens[exec->count][1] == '>'
			&& tokens[exec->count][2] == '\0'))
			exec->redir_out++;
		exec->count++;
	}
}

int	count_pipes(char **tokens)
{
	int	pipe_count;
	int	i;

	pipe_count = 0;
	i = 0;
	while (tokens && tokens[i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '\0')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}
