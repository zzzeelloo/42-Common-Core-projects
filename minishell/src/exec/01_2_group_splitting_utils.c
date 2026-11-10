/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_2_group_splitting_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:25:31 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/11 20:20:25 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../libft/libft.h"

int	is_token(const char *tok, const char *s)
{
	return (ft_strcmp(tok, s) == 0);
}

void	is_infile(t_exec *exec, char **tokens)
{
	if (exec->i + 1 < exec->count)
		assign_infile_redirection(exec, tokens);
	exec->i = exec->i + 2;
}

void	is_notpipe(t_exec *exec, char **tokens)
{
	if (exec->ncmd < exec->count && exec->i < exec->count)
	{
		exec->cmds[exec->ncmd] = ft_strdup(tokens[exec->i]);
		exec->ncmd = exec->ncmd + 1;
	}
	exec->i = exec->i + 1;
}

void	is_outfile(t_exec *exec, char **tokens)
{
	if (exec->i + 1 < exec->count)
		assign_outfile_redirection(exec, tokens);
	exec->i = exec->i + 2;
}
