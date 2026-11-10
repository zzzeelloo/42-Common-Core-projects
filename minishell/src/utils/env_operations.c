/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:33:00 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 17:42:17 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	**copy_basic_env(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	count = count_env_vars(envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			ft_freesplit(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	replace_env_var(char ***env_ptr, int index, char *name, char *value)
{
	char	*new_var_string;
	char	*old_var;

	new_var_string = create_env_string(name, value);
	if (!new_var_string)
		return (1);
	old_var = (*env_ptr)[index];
	(*env_ptr)[index] = new_var_string;
	free(old_var);
	return (0);
}

static int	copy_env_vars(char **new_env, char **old_env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_new_env_var(char ***env_ptr, char *name, char *value)
{
	char	**new_env;
	char	*new_var_string;
	int		count;

	new_var_string = create_env_string(name, value);
	if (!new_var_string)
		return (1);
	count = count_env_vars(*env_ptr);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(new_var_string);
		return (1);
	}
	if (copy_env_vars(new_env, *env_ptr, count))
	{
		free(new_env);
		free(new_var_string);
		return (1);
	}
	new_env[count] = new_var_string;
	new_env[count + 1] = NULL;
	ft_freesplit(*env_ptr);
	*env_ptr = new_env;
	return (0);
}

int	set_env_var_global(char ***env_ptr, char *name, char *value)
{
	int	var_index;

	if (!env_ptr || !*env_ptr || !name)
		return (-1);
	var_index = find_env_index(*env_ptr, name);
	if (var_index != -1)
		return (replace_env_var(env_ptr, var_index, name, value));
	else
		return (add_new_env_var(env_ptr, name, value));
}
