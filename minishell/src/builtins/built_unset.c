/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:33:50 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 17:47:21 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/utils.h"

int	unset_is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	unset_variable(char *var_name, char ***env_ptr)
{
	if (!unset_is_valid_identifier(var_name))
	{
		ft_putstr_fd("unset: ", STDERR_FILENO);
		ft_putstr_fd(var_name, STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	if (unset_env_var_global(env_ptr, var_name) != 0)
	{
		ft_putstr_fd("unset: error unsetting environment variable\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	builtin_unset(char **args, char ***env_ptr)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!args[1])
	{
		return (0);
	}
	while (args[i])
	{
		if (unset_variable(args[i], env_ptr) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
