/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_3_heredoc_processing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:20:33 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/10 19:34:19 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	write_line_to_pipe(int write_fd, char *line)
{
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
}

static void	read_heredoc_lines(int write_fd, const char *delimiter)
{
	char	*line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(write_fd);
			break ;
		}
		if (check_delimiter(line, delimiter, delimiter_len))
		{
			free(line);
			close(write_fd);
			break ;
		}
		write_line_to_pipe(write_fd, line);
		free(line);
	}
}

int	create_heredoc_pipe(const char *delimiter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	read_heredoc_lines(pipe_fd[1], delimiter);
	return (pipe_fd[0]);
}

void	cleanup_heredoc(t_cmd_redir *cmd_redir)
{
	if (cmd_redir->heredoc_delimiter)
	{
		free(cmd_redir->heredoc_delimiter);
		cmd_redir->heredoc_delimiter = NULL;
	}
	if (cmd_redir->heredoc_fd != -1)
	{
		close(cmd_redir->heredoc_fd);
		cmd_redir->heredoc_fd = -1;
	}
	cmd_redir->is_heredoc = 0;
}

void	cleanup_all_heredocs(t_exec *exec)
{
	int	i;

	if (!exec || !exec->cmd_redirs)
		return ;
	i = 0;
	while (i < exec->total_commands)
	{
		cleanup_heredoc(&exec->cmd_redirs[i]);
		i++;
	}
}
