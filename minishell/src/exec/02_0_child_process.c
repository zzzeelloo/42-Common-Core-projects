/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_0_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:19:38 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/10 19:22:50 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	close_pipe_fds(t_exec *exec)
{
	if (exec->pipex.fd[0] != -1)
	{
		if (close(exec->pipex.fd[0]) == -1)
			perror("close pipex.fd[0]");
		exec->pipex.fd[0] = -1;
	}
	if (exec->pipex.fd[1] != -1)
	{
		if (close(exec->pipex.fd[1]) == -1)
			perror("close pipex.fd[1]");
		exec->pipex.fd[1] = -1;
	}
}

void	setup_redirections(t_exec *exec)
{
	child_signals_monitoring();
	open_files_for_current_command(exec);
	setup_input_redirection(exec);
	setup_output_redirection(exec);
	close_pipe_fds(exec);
	cleanup_all_open_fds();
}
