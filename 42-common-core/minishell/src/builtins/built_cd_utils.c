/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:30:23 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 20:58:58 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parsing.h"
#include "../../includes/utils.h"

char	*get_env_value(char *key)
{
	if (!key)
		return (NULL);
	return (getenv(key));
}

char	*get_env_value_from_envp(char *key, char **envp)
{
	int	i;
	int	len;

	if (!key || !envp)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	set_env_value(char *key, char *value)
{
	if (!key || !value)
		return (-1);
	if (my_setenv(key, value) != 0)
		return (-1);
	return (0);
}
