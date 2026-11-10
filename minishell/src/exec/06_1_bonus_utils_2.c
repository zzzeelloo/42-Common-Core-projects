/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_1_bonus_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:38:27 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:38:28 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

int	check_delimiter(char *line, const char *delimiter, size_t delimiter_len)
{
	if (ft_strncmp(line, delimiter, delimiter_len) == 0
		&& line[delimiter_len] == '\0')
		return (1);
	return (0);
}

static int	open_input_file(t_exec *exec, int i)
{
	if (exec->cmd_redirs[i].infile == NULL)
		return (0);
	if (access(exec->cmd_redirs[i].infile, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_redirs[i].infile, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (-1);
	}
	if (access(exec->cmd_redirs[i].infile, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_redirs[i].infile, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (-1);
	}
	exec->cmd_redirs[i].infile_fd = open(exec->cmd_redirs[i].infile, O_RDONLY);
	if (exec->cmd_redirs[i].infile_fd == -1)
	{
		perror(exec->cmd_redirs[i].infile);
		return (-1);
	}
	return (0);
}

static int	check_output_directory(t_exec *exec, int i)
{
	if (!check_parent_directory_exists(exec->cmd_redirs[i].outfile))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_redirs[i].outfile, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		if (exec->cmd_redirs[i].infile_fd != -1)
			close(exec->cmd_redirs[i].infile_fd);
		return (-1);
	}
	return (0);
}

static int	open_output_file(t_exec *exec, int i)
{
	if (exec->cmd_redirs[i].outfile == NULL)
		return (0);
	if (check_output_directory(exec, i) == -1)
		return (-1);
	if (exec->cmd_redirs[i].append)
		exec->cmd_redirs[i].outfile_fd = open(exec->cmd_redirs[i].outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exec->cmd_redirs[i].outfile_fd = open(exec->cmd_redirs[i].outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec->cmd_redirs[i].outfile_fd == -1)
	{
		perror(exec->cmd_redirs[i].outfile);
		if (exec->cmd_redirs[i].infile_fd != -1)
			close(exec->cmd_redirs[i].infile_fd);
		return (-1);
	}
	return (0);
}

void	open_files_for_pipeline(t_exec *exec, int group_count)
{
	int	i;

	i = 0;
	while (i < group_count)
	{
		if (open_input_file(exec, i) == -1)
			return ;
		if (open_output_file(exec, i) == -1)
			return ;
		i++;
	}
}
