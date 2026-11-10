/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_3_pipeline_process_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:47:00 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/11 18:47:06 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/utils.h"

int	handle_parent_pipes(int prev_pipe_read, int i, int group_count,
		int *pipe_fd)
{
	if (prev_pipe_read != -1)
	{
		if (close(prev_pipe_read) == -1)
			perror("close prev_pipe_read");
	}
	if (i < group_count - 1)
	{
		if (close(pipe_fd[1]) == -1)
			perror("close pipe_fd[1]");
		return (pipe_fd[0]);
	}
	return (-1);
}

int	create_pipe_for_command(int i, int group_count, int pipe_fd[2],
		int *pipe_created)
{
	if (i < group_count - 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
		*pipe_created = 1;
	}
	return (0);
}
