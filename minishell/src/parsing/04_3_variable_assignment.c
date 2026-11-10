/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_3_variable_assignment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:03:42 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 17:47:21 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/utils.h"

int	is_variable_assignment(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	if (str[i] != '=')
		return (0);
	return (1);
}

int	process_variable_assignment(const char *assignment, char ***env_ptr)
{
	char	*equals_pos;
	char	*var_name;
	char	*var_value;
	int		result;

	equals_pos = ft_strchr(assignment, '=');
	if (!equals_pos)
		return (0);
	var_name = ft_substr(assignment, 0, equals_pos - assignment);
	if (!var_name)
		return (0);
	var_value = ft_strdup(equals_pos + 1);
	if (!var_value)
	{
		free(var_name);
		return (0);
	}
	result = set_env_var_global(env_ptr, var_name, var_value);
	free(var_name);
	free(var_value);
	return (result == 0);
}

int	has_variable_assignment(char **tokens)
{
	int	i;

	if (!tokens || !tokens[0])
		return (0);
	if (!is_variable_assignment(tokens[0]))
		return (0);
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0 || ft_strcmp(tokens[i],
				"<<") == 0)
		{
			i++;
			if (tokens[i])
				i++;
			continue ;
		}
		if (!is_variable_assignment(tokens[i]))
			return (0);
		i++;
	}
	return (1);
}

int	process_variable_assignments(char **tokens, char ***env_ptr)
{
	int	i;
	int	success;

	if (!tokens)
		return (0);
	success = 1;
	i = 0;
	while (tokens[i])
	{
		if (is_variable_assignment(tokens[i]))
		{
			if (!process_variable_assignment(tokens[i], env_ptr))
				success = 0;
		}
		i++;
	}
	return (success);
}
