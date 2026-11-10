/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_0_file_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:33:07 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:33:20 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

static int	check_input_file_access(t_exec *exec)
{
	if (access(exec->cmd_redirs[0].infile, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_redirs[0].infile, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_exit_status = 1;
		return (-1);
	}
	if (access(exec->cmd_redirs[0].infile, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_redirs[0].infile, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

int	open_input_file_single(t_exec *exec)
{
	if (exec->cmd_redirs[0].infile == NULL)
		return (0);
	if (check_input_file_access(exec) == -1)
		return (-1);
	exec->cmd_redirs[0].infile_fd = open(exec->cmd_redirs[0].infile, O_RDONLY);
	if (exec->cmd_redirs[0].infile_fd == -1)
	{
		perror(exec->cmd_redirs[0].infile);
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

static int	check_output_directory_single(t_exec *exec)
{
	if (!check_parent_directory_exists(exec->cmd_redirs[0].outfile))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_redirs[0].outfile, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		if (exec->cmd_redirs[0].infile_fd != -1)
			close(exec->cmd_redirs[0].infile_fd);
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

int	open_output_file_single(t_exec *exec)
{
	if (exec->cmd_redirs[0].outfile == NULL)
		return (0);
	if (check_output_directory_single(exec) == -1)
		return (-1);
	if (exec->cmd_redirs[0].append)
		exec->cmd_redirs[0].outfile_fd = open(exec->cmd_redirs[0].outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exec->cmd_redirs[0].outfile_fd = open(exec->cmd_redirs[0].outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec->cmd_redirs[0].outfile_fd == -1)
	{
		perror(exec->cmd_redirs[0].outfile);
		if (exec->cmd_redirs[0].infile_fd != -1)
			close(exec->cmd_redirs[0].infile_fd);
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

void	apply_redirections_for_builtin(t_exec *exec, int *saved_stdin,
		int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (exec->cmd_redirs[0].is_heredoc)
	{
		if (dup2(exec->cmd_redirs[0].heredoc_fd, STDIN_FILENO) == -1)
			perror("dup2 heredoc");
	}
	else if (exec->cmd_redirs[0].infile_fd != -1)
	{
		if (dup2(exec->cmd_redirs[0].infile_fd, STDIN_FILENO) == -1)
			perror("dup2 infile");
	}
	if (exec->cmd_redirs[0].outfile_fd != -1)
	{
		if (dup2(exec->cmd_redirs[0].outfile_fd, STDOUT_FILENO) == -1)
			perror("dup2 outfile");
	}
}
