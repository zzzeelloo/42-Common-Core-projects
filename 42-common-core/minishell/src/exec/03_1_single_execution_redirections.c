/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_1_single_execution_redirections.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:28:47 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/10 19:31:43 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	setup_input_redirection_one(t_exec *exec)
{
	if (exec->cmd_redirs[0].is_heredoc)
	{
		if (dup2(exec->cmd_redirs[0].heredoc_fd, STDIN_FILENO) == -1)
			free_pipex(exec, 1, "dup2", strerror(errno));
		close(exec->cmd_redirs[0].heredoc_fd);
	}
	else if (exec->cmd_redirs[0].infile_fd != -1)
	{
		if (dup2(exec->cmd_redirs[0].infile_fd, STDIN_FILENO) == -1)
			free_pipex(exec, 1, "dup2", strerror(errno));
		close(exec->cmd_redirs[0].infile_fd);
	}
}

void	setup_output_redirection_one(t_exec *exec)
{
	if (exec->cmd_redirs[0].outfile_fd != -1)
	{
		if (dup2(exec->cmd_redirs[0].outfile_fd, STDOUT_FILENO) == -1)
			free_pipex(exec, 1, "dup2", strerror(errno));
		close(exec->cmd_redirs[0].outfile_fd);
	}
}
