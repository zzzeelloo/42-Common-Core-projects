/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_1_single_execution_setup.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:28:47 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/12 17:57:14 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	initialize_single_command_pipex(t_exec *exec, char **envp)
{
	pipex_init(exec, envp);
	exec->pipex.cmd_nbr = 1;
	exec->pipex.pids = malloc(sizeof(pid_t) * 1);
	if (!exec->pipex.pids)
	{
		perror("malloc");
		ft_freesplit(exec->pipex.paths);
		exec->pipex.paths = NULL;
		return (-1);
	}
	exec->pipex.i = 0;
	exec->i = 0;
	return (0);
}

static int	validate_and_open_single_command_files(t_exec *exec)
{
	if (exec->redir == -1)
	{
		free(exec->pipex.pids);
		exec->pipex.pids = NULL;
		ft_freesplit(exec->pipex.paths);
		exec->pipex.paths = NULL;
		return (-1);
	}
	if (open_files_for_single_command(exec) == -1)
	{
		free(exec->pipex.pids);
		exec->pipex.pids = NULL;
		ft_freesplit(exec->pipex.paths);
		exec->pipex.paths = NULL;
		return (-1);
	}
	return (0);
}

int	setup_single_command_basic(t_exec *exec, char **envp)
{
	if (initialize_single_command_pipex(exec, envp) == -1)
		return (-1);
	if (validate_and_open_single_command_files(exec) == -1)
		return (-1);
	return (0);
}

void	handle_env_special_case(t_exec *exec)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(exec->groups[0][1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	g_exit_status = 127;
}

void	handle_builtin_execution(t_exec *exec, char ***env_ptr)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = -1;
	saved_stdout = -1;
	apply_redirections_for_builtin(exec, &saved_stdin, &saved_stdout);
	g_exit_status = execute_builtin_with_exec(exec->groups[0], env_ptr, exec);
	restore_original_fds(saved_stdin, saved_stdout);
}
