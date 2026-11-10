/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:00:24 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 20:10:14 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	open_infile(t_exec *exec, char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		free_pipex(exec, 1, "No such file or directory", infile);
	}
	if (access(infile, R_OK) == -1)
	{
		free_pipex(exec, 1, "permission denied", infile);
		return ;
	}
	exec->pipex.infile = open(infile, O_RDONLY);
	if (exec->pipex.infile == -1)
		free_pipex(exec, 1, "<open_infile>", strerror(errno));
}

void	open_outfile_utils(t_exec *exec, char *outfile, int mode)
{
	if (access(outfile, F_OK) == 0)
	{
		if (access(outfile, W_OK) == -1)
			free_pipex(exec, 1, "permission denied", outfile);
	}
	if (mode == 0)
		exec->pipex.outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	else if (mode == 1)
		exec->pipex.outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	if (exec->pipex.outfile == -1)
		free_pipex(exec, 1, "<open_outfile>", strerror(errno));
}
