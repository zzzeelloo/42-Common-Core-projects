/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_0_single_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:20:03 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/12 18:04:35 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_one(t_exec *exec, char **cmd_args, char **envp)
{
	exec->pipex.pids[exec->pipex.i] = fork();
	if (exec->pipex.pids[exec->pipex.i] == -1)
		free_pipex(exec, 1, "pid", strerror(errno));
	if (exec->pipex.pids[exec->pipex.i] == 0)
	{
		child_signals_monitoring();
		setup_input_redirection_one(exec);
		setup_output_redirection_one(exec);
		cleanup_all_open_fds();
		execute_bonus_args(exec, cmd_args, envp);
	}
}

static void	handle_external_command_execution(t_exec *exec, char **envp)
{
	int	status;
	int	sig;

	exec_one(exec, exec->groups[0], envp);
	signal(SIGINT, SIG_IGN);
	waitpid(exec->pipex.pids[0], &status, 0);
	signals_monitoring();
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		g_exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
	}
}

static void	execute_single_command_logic(t_exec *exec, char ***env_ptr)
{
	if (!exec->groups[0] || !exec->groups[0][0])
		return ;
	if (is_builtin(exec->groups[0][0]))
		handle_builtin_execution(exec, env_ptr);
	else
		handle_external_command_execution(exec, *env_ptr);
}

static void	cleanup_single_command(t_exec *exec)
{
	if (exec->cmd_redirs[0].infile_fd != -1)
		close(exec->cmd_redirs[0].infile_fd);
	if (exec->cmd_redirs[0].outfile_fd != -1)
		close(exec->cmd_redirs[0].outfile_fd);
	if (exec->cmd_redirs[0].is_heredoc)
		cleanup_heredoc(&exec->cmd_redirs[0]);
	free(exec->pipex.pids);
	exec->pipex.pids = NULL;
	ft_freesplit(exec->pipex.paths);
	exec->pipex.paths = NULL;
}

void	handle_single_command(t_exec *exec, char ***env_ptr)
{
	if (setup_single_command_basic(exec, *env_ptr) == -1)
		return ;
	execute_single_command_logic(exec, env_ptr);
	cleanup_single_command(exec);
}
