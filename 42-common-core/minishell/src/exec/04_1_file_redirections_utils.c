/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_file_redirections_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:33:39 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:34:07 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

int	open_files_for_single_command(t_exec *exec)
{
	if (open_input_file_single(exec) == -1)
		return (-1);
	if (open_output_file_single(exec) == -1)
		return (-1);
	return (0);
}

void	restore_original_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
