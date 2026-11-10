/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:32:50 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 17:47:21 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/utils.h"
#include "../libft/libft.h"

static int	export_variable(char *arg, char ***env_ptr)
{
	char	*equals_pos;

	if (arg[0] == '=')
	{
		print_export_error(arg, NULL);
		return (1);
	}
	equals_pos = ft_strchr(arg, '=');
	if (equals_pos)
		return (export_with_value(arg, equals_pos, env_ptr));
	else
		return (export_without_value(arg, env_ptr));
}

static int	has_valid_export_args(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i][0] != '\0')
			return (1);
		i++;
	}
	return (0);
}

static int	process_export_args(char **args, char ***env_ptr)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
		{
			if (export_variable(args[i], env_ptr) != 0)
				exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}

int	builtin_export(char **args, char ***env_ptr)
{
	if (!args[1] || !has_valid_export_args(args))
	{
		print_export_vars(*env_ptr);
		return (0);
	}
	return (process_export_args(args, env_ptr));
}
