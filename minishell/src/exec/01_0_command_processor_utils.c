/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_0_command_processor_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:28:47 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/12 17:53:26 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

void	cleanup_empty_group(t_exec *exec)
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

void	handle_empty_group_redirections(t_exec *exec, char ***env_ptr)
{
	if (!exec->cmd_redirs || exec->total_commands <= 0)
		return ;
	pipex_init(exec, *env_ptr);
	exec->pipex.cmd_nbr = 1;
	exec->pipex.pids = malloc(sizeof(pid_t) * 1);
	if (!exec->pipex.pids)
	{
		perror("malloc");
		ft_freesplit(exec->pipex.paths);
		exec->pipex.paths = NULL;
		return ;
	}
	exec->pipex.i = 0;
	exec->i = 0;
	if (open_files_for_single_command(exec) != -1)
		cleanup_empty_group(exec);
}
