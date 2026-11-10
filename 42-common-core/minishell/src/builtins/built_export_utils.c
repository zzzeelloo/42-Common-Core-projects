/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
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

int	is_valid_identifier(char *str)
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

int	export_with_value(char *arg, char *equals_pos, char ***env_ptr)
{
	char	*key;
	char	*value;
	int		result;

	key = ft_substr(arg, 0, equals_pos - arg);
	value = equals_pos + 1;
	if (!is_valid_identifier(key))
	{
		print_export_error(arg, key);
		free(key);
		return (1);
	}
	result = set_env_var_global(env_ptr, key, value);
	free(key);
	if (result != 0)
	{
		ft_putstr_fd("export: error setting environment variable\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	export_without_value(char *arg, char ***env_ptr)
{
	int		result;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg, NULL);
		return (1);
	}
	result = set_env_var_global(env_ptr, arg, "");
	if (result != 0)
	{
		ft_putstr_fd("export: error setting environment variable\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}
