/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_3_bonus_execution_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:32:34 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:32:40 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

void	check_exec_file(t_exec *exec, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_pipex(exec, 127, cmd, "no such file or directory");
	if (access(cmd, X_OK) == -1)
		free_pipex(exec, 126, cmd, "Permission denied");
	exec->pipex.cmd = ft_strdup(cmd);
	if (!exec->pipex.cmd)
		free_pipex(exec, 1, "malloc", "Memory allocation failed");
}

void	check_exec(t_exec *exec, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_pipex(exec, 127, cmd, "command not found");
	if (access(cmd, X_OK) == -1)
		free_pipex(exec, 126, cmd, "Permission denied");
}

static void	handle_directory_error(t_exec *exec, char **cmd_args)
{
	if (strchr(cmd_args[0], '/'))
		free_pipex(exec, 126, exec->pipex.cmd, "is a directory");
	else
		free_pipex(exec, 127, cmd_args[0], "command not found");
}

void	check_if_directory(t_exec *exec, char **cmd_args)
{
	struct stat	sb;

	if (stat(exec->pipex.cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
		handle_directory_error(exec, cmd_args);
}

void	handle_execve_error(t_exec *exec)
{
	if (errno == EACCES || errno == EISDIR)
		free_pipex(exec, 126, "pipex: execve", strerror(errno));
	if (errno == ENOENT || errno == EPERM)
		free_pipex(exec, 127, "pipex: execve", strerror(errno));
	if (errno == ENOTDIR)
		free_pipex(exec, 127, "pipex: execve", strerror(errno));
	free_pipex(exec, 1, "execve", strerror(errno));
}
