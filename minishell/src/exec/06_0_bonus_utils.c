/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_0_bonus_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:21:06 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/10 19:38:04 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../includes/parsing.h"

int	contains_slash(const char *s)
{
	while (s && *s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}

static void	init_pipex_values(t_exec *exec)
{
	exec->pipex = (t_pipex){0};
	exec->pipex.infile = -1;
	exec->pipex.outfile = -1;
	exec->pipex.here_doc = 1;
	exec->pipex.i = -1;
	exec->pipex.envp = 1;
}

static void	setup_paths_from_process_env(t_exec *exec)
{
	char	*path;

	path = getenv("PATH");
	if (!path || *path == '\0')
	{
		exec->pipex.envp = 0;
		exec->pipex.paths = NULL;
		return ;
	}
	exec->pipex.paths = ft_split(path, ':');
	if (!exec->pipex.paths)
		if (errno == ENOMEM)
			free_pipex(exec, -1, "malloc", strerror(errno));
}

void	pipex_init(t_exec *exec, char **envp)
{
	(void)envp;
	init_pipex_values(exec);
	setup_paths_from_process_env(exec);
}

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
