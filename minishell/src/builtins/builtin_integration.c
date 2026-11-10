/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_integration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:45:00 by angus             #+#    #+#             */
/*   Updated: 2025/07/01 12:45:00 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <unistd.h>

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **args, char ***env_ptr)
{
	if (!args || !args[0])
		return (-1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, env_ptr));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env_ptr));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, env_ptr));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, env_ptr));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	return (-1);
}

int	execute_builtin_with_exec(char **args, char ***env_ptr, t_exec *exec)
{
	if (!args || !args[0])
		return (-1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, env_ptr));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env_ptr));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, env_ptr));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, env_ptr));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit_with_cleanup(args, exec));
	return (-1);
}
