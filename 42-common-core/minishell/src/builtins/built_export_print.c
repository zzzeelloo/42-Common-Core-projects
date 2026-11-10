/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:32:50 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 21:09:59 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/utils.h"
#include "../libft/libft.h"

void	print_export_var_with_value(char *env_var, char *equals_pos)
{
	char	*key;
	char	*value;

	key = ft_substr(env_var, 0, equals_pos - env_var);
	ft_putstr_fd(key, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	value = equals_pos + 1;
	ft_putstr_fd(value, STDOUT_FILENO);
	ft_putstr_fd("\"", STDOUT_FILENO);
	free(key);
}

void	print_export_var_without_value(char *env_var)
{
	ft_putstr_fd(env_var, STDOUT_FILENO);
}

void	print_export_vars(char **envp)
{
	int		i;
	char	*equals_pos;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		equals_pos = ft_strchr(envp[i], '=');
		if (equals_pos)
			print_export_var_with_value(envp[i], equals_pos);
		else
			print_export_var_without_value(envp[i]);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}

void	print_export_error(char *arg, char *key)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	if (key)
		ft_putstr_fd(key, STDERR_FILENO);
	else
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}
