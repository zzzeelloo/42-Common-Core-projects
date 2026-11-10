/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:56:38 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:58:34 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	check_parent_directory_exists(char *filepath)
{
	char	*last_slash;
	char	*parent_dir;
	int		result;

	if (!filepath)
		return (0);
	last_slash = ft_strrchr(filepath, '/');
	if (!last_slash)
		return (1);
	if (last_slash == filepath)
		return (1);
	parent_dir = ft_substr(filepath, 0, last_slash - filepath);
	if (!parent_dir)
		return (0);
	result = (access(parent_dir, F_OK) == 0);
	free(parent_dir);
	return (result);
}
