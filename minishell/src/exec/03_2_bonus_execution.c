/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_2_bonus_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:19:56 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/12 17:51:11 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <sys/stat.h>

static char	*create_cmd_path(t_exec *exec, char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		free_pipex(exec, 1, "malloc", strerror(errno));
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		free_pipex(exec, 1, "malloc", strerror(errno));
	return (full_path);
}

void	find_path(t_exec *exec, char *cmd)
{
	int	i;

	i = -1;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			check_exec_file(exec, cmd);
			return ;
		}
		return ;
	}
	while (exec->pipex.envp && exec->pipex.paths && exec->pipex.paths[++i])
	{
		exec->pipex.cmd = create_cmd_path(exec, exec->pipex.paths[i], cmd);
		if (access(exec->pipex.cmd, F_OK) == 0)
			break ;
		free(exec->pipex.cmd);
		exec->pipex.cmd = NULL;
	}
	if (exec->pipex.cmd)
		check_exec(exec, exec->pipex.cmd);
}

static void	handle_builtin_execution_bonus(t_exec *exec, char **cmd_args,
		char **envp)
{
	if (is_builtin(cmd_args[0]))
	{
		g_exit_status = execute_builtin_with_exec(cmd_args, &envp, exec);
		cleanup_child_memory_full(exec);
		exit(g_exit_status);
	}
}

static void	execute_external_command(t_exec *exec, char **cmd_args, char **envp)
{
	char	*cmd_to_exec;

	find_path(exec, cmd_args[0]);
	if (!exec->pipex.cmd)
	{
		if (!exec->pipex.envp && !contains_slash(cmd_args[0]))
			free_pipex(exec, 127, cmd_args[0], "No such file or directory");
		free_pipex(exec, 127, cmd_args[0], "command not found");
	}
	check_if_directory(exec, cmd_args);
	exec->pipex.cmd_args = cmd_args;
	cmd_to_exec = exec->pipex.cmd;
	cleanup_child_memory_for_execve(exec);
	if (execve(cmd_to_exec, cmd_args, envp) == -1)
	{
		perror("execve");
		exit(126);
	}
}

void	execute_bonus_args(t_exec *exec, char **cmd_args, char **envp)
{
	if (!cmd_args || !cmd_args[0] || !cmd_args[0][0])
	{
		cleanup_child_memory_full(exec);
		exit(0);
	}
	handle_builtin_execution_bonus(exec, cmd_args, envp);
	execute_external_command(exec, cmd_args, envp);
}
