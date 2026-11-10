/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setunset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:34:00 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 18:42:05 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*find_env_value(char **envp, const char *name)
{
	int		index;
	char	*equals_pos;

	index = find_env_index(envp, name);
	if (index == -1)
		return (NULL);
	equals_pos = ft_strchr(envp[index], '=');
	if (!equals_pos)
		return (NULL);
	return (equals_pos + 1);
}

int	unset_env_var_global(char ***env_ptr, char *name)
{
	int	index;
	int	i;

	if (!env_ptr || !*env_ptr || !name)
		return (-1);
	index = find_env_index(*env_ptr, name);
	if (index == -1)
		return (0);
	free((*env_ptr)[index]);
	i = index;
	while ((*env_ptr)[i + 1])
	{
		(*env_ptr)[i] = (*env_ptr)[i + 1];
		i++;
	}
	(*env_ptr)[i] = NULL;
	return (0);
}

int	my_setenv(char *name, char *value)
{
	(void)name;
	(void)value;
	return (0);
}

int	my_unsetenv(char *name)
{
	(void)name;
	return (0);
}
