/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_2_child_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:29:53 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:29:54 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	handle_infile_redirection(t_exec *exec, int current_cmd)
{
	if (exec->cmd_redirs[current_cmd].infile != NULL)
	{
		check_infile_access(exec, current_cmd);
		open_infile_fd(exec, current_cmd);
	}
}

void	handle_outfile_redirection(t_exec *exec, int current_cmd)
{
	if (exec->cmd_redirs[current_cmd].outfile != NULL)
	{
		check_outfile_directory(exec, current_cmd);
		open_outfile_fd(exec, current_cmd);
		if (exec->cmd_redirs[current_cmd].outfile_fd == -1)
			handle_outfile_error(exec, current_cmd);
	}
}

void	open_files_for_current_command(t_exec *exec)
{
	int	current_cmd;

	current_cmd = exec->pipex.i;
	handle_infile_redirection(exec, current_cmd);
	handle_outfile_redirection(exec, current_cmd);
}

void	setup_input_redirection(t_exec *exec)
{
	int	current_cmd;

	current_cmd = exec->pipex.i;
	if (exec->cmd_redirs[current_cmd].is_heredoc)
	{
		if (dup2(exec->cmd_redirs[current_cmd].heredoc_fd, STDIN_FILENO) == -1)
			free_pipex(exec, 1, "dup2", strerror(errno));
		close(exec->cmd_redirs[current_cmd].heredoc_fd);
	}
	else if (exec->cmd_redirs[current_cmd].infile_fd != -1)
	{
		if (dup2(exec->cmd_redirs[current_cmd].infile_fd, STDIN_FILENO) == -1)
			free_pipex(exec, 1, "dup2", strerror(errno));
		close(exec->cmd_redirs[current_cmd].infile_fd);
	}
	else if (exec->pipex.fd[0] != -1)
	{
		if (dup2(exec->pipex.fd[0], STDIN_FILENO) == -1)
			free_pipex(exec, 1, "dup2", strerror(errno));
	}
}

void	setup_output_redirection(t_exec *exec)
{
	int	current_cmd;

	current_cmd = exec->pipex.i;
	if (exec->cmd_redirs[current_cmd].outfile_fd != -1)
	{
		if (dup2(exec->cmd_redirs[current_cmd].outfile_fd, STDOUT_FILENO) == -1)
			free_pipex(exec, 1, "dup2", strerror(errno));
		close(exec->cmd_redirs[current_cmd].outfile_fd);
	}
	else if (exec->pipex.fd[1] != -1)
	{
		if (dup2(exec->pipex.fd[1], STDOUT_FILENO) == -1)
			free_pipex(exec, 1, "dup2", strerror(errno));
	}
}
