/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_4_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:34:31 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 16:52:52 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../libft/libft.h"

void	is_heredoc(t_exec *exec, char **tokens)
{
	if (exec->i + 1 < exec->count)
		assign_heredoc_redirection(exec, tokens);
	exec->i = exec->i + 2;
}

void	cleanup_previous_heredoc(t_exec *exec)
{
	if (exec->cmd_redirs[exec->ng].is_heredoc)
		cleanup_heredoc(&exec->cmd_redirs[exec->ng]);
}

void	setup_new_heredoc(t_exec *exec, char **tokens)
{
	exec->cmd_redirs[exec->ng].heredoc_delimiter = ft_strdup(tokens[exec->i
			+ 1]);
	exec->cmd_redirs[exec->ng].is_heredoc = 1;
	exec->cmd_redirs[exec->ng].heredoc_fd = create_heredoc_pipe(tokens[exec->i
			+ 1]);
	if (exec->cmd_redirs[exec->ng].heredoc_fd == -1)
		ft_printf("minishell: heredoc: pipe creation failed\n");
}

void	assign_heredoc_redirection(t_exec *exec, char **tokens)
{
	if (exec->ng < exec->total_commands)
	{
		cleanup_previous_heredoc(exec);
		setup_new_heredoc(exec, tokens);
	}
}
