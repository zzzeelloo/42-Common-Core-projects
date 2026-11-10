/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_1_child_file_ops.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:29:30 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:29:38 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	check_infile_access(t_exec *exec, int current_cmd)
{
	if (access(exec->cmd_redirs[current_cmd].infile, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_redirs[current_cmd].infile, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(1);
	}
	if (access(exec->cmd_redirs[current_cmd].infile, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_redirs[current_cmd].infile, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		exit(1);
	}
}

void	open_infile_fd(t_exec *exec, int current_cmd)
{
	exec->cmd_redirs[current_cmd].infile_fd
		= open(exec->cmd_redirs[current_cmd].infile, O_RDONLY);
	if (exec->cmd_redirs[current_cmd].infile_fd == -1)
	{
		perror(exec->cmd_redirs[current_cmd].infile);
		exit(1);
	}
}

void	check_outfile_directory(t_exec *exec, int current_cmd)
{
	if (!check_parent_directory_exists(exec->cmd_redirs[current_cmd].outfile))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_redirs[current_cmd].outfile, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		if (exec->cmd_redirs[current_cmd].infile_fd != -1)
			close(exec->cmd_redirs[current_cmd].infile_fd);
		exit(1);
	}
}

void	open_outfile_fd(t_exec *exec, int current_cmd)
{
	if (exec->cmd_redirs[current_cmd].append)
		exec->cmd_redirs[current_cmd].outfile_fd
			= open(exec->cmd_redirs[current_cmd].outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exec->cmd_redirs[current_cmd].outfile_fd
			= open(exec->cmd_redirs[current_cmd].outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	handle_outfile_error(t_exec *exec, int current_cmd)
{
	perror(exec->cmd_redirs[current_cmd].outfile);
	if (exec->cmd_redirs[current_cmd].infile_fd != -1)
		close(exec->cmd_redirs[current_cmd].infile_fd);
	exit(1);
}
