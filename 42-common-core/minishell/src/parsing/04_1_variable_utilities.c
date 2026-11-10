/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_variable_utilities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:36:13 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:37:18 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	*search_in_env(const char *var_name, char **envp)
{
	char	*value;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strlen(var_name) == 0)
		return (ft_strdup(""));
	value = find_env_value(envp, var_name);
	if (value)
	{
		value = ft_strdup(value);
		if (value)
			return (value);
		else
			return (ft_strdup(""));
	}
	return (ft_strdup(""));
}

char	*get_env_var_value(const char *var_name, char **envp,
		int last_exit_status)
{
	if (!var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(last_exit_status));
	if (ft_strcmp(var_name, "UID") == 0)
		return (ft_itoa(getuid()));
	return (search_in_env(var_name, envp));
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
