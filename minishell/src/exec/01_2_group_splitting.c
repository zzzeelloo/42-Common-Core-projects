/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_2_group_splitting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:20:50 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/10 15:43:28 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../libft/libft.h"
#include <fcntl.h>

static void	finalize_current_group(t_exec *exec)
{
	finalize_group(exec);
	if (exec->group)
	{
		exec->groups[exec->ng] = exec->group;
		exec->ng = exec->ng + 1;
		exec->ncmd = 0;
	}
}

static void	handle_pipe(t_exec *exec)
{
	if (exec->ncmd > 0)
		finalize_current_group(exec);
	exec->i = exec->i + 1;
}

void	assign_infile_redirection(t_exec *exec, char **tokens)
{
	if (exec->ng < exec->total_commands)
	{
		if (exec->total_commands == 1 && exec->redir != -1)
		{
			if (access(tokens[exec->i + 1], F_OK) == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(tokens[exec->i + 1], STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				g_exit_status = 1;
				exec->redir = -1;
				return ;
			}
		}
		if (exec->cmd_redirs[exec->ng].infile)
			free(exec->cmd_redirs[exec->ng].infile);
		exec->cmd_redirs[exec->ng].infile = ft_strdup(tokens[exec->i + 1]);
	}
}

void	assign_outfile_redirection(t_exec *exec, char **tokens)
{
	if (exec->ng < exec->total_commands)
	{
		open_outfile_utils(exec, tokens[exec->i + 1], 1);
		if (exec->cmd_redirs[exec->ng].outfile)
			free(exec->cmd_redirs[exec->ng].outfile);
		exec->cmd_redirs[exec->ng].outfile = ft_strdup(tokens[exec->i + 1]);
		if (is_token(tokens[exec->i], ">>"))
			exec->cmd_redirs[exec->ng].append = 1;
		else
			exec->cmd_redirs[exec->ng].append = 0;
	}
}

void	split_groups(t_exec *exec, char **tokens)
{
	while (exec->i < exec->count)
	{
		if (is_token(tokens[exec->i], "<<") && exec->i + 1 < exec->count)
			is_heredoc(exec, tokens);
		else if (is_token(tokens[exec->i], "<") && exec->i + 1 < exec->count)
			is_infile(exec, tokens);
		else if ((is_token(tokens[exec->i], ">")
				|| is_token(tokens[exec->i], ">>"))
			&& exec->i + 1 < exec->count)
			is_outfile(exec, tokens);
		else if (is_token(tokens[exec->i], "|"))
			handle_pipe(exec);
		else
			is_notpipe(exec, tokens);
	}
}
