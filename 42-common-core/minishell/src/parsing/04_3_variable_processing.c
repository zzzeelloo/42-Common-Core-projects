/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_3_variable_processing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:43:42 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:43:51 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../libft/libft.h"

int	extract_positional_param(const char **str_ptr, t_str_builder *var_name_sb)
{
	if (!sb_append_char(var_name_sb, **str_ptr))
	{
		sb_free(var_name_sb);
		return (0);
	}
	(*str_ptr)++;
	return (1);
}

int	extract_variable_name(const char **str_ptr, t_str_builder *var_name_sb)
{
	while (is_valid_var_char(**str_ptr))
	{
		if (!sb_append_char(var_name_sb, **str_ptr))
		{
			sb_free(var_name_sb);
			return (0);
		}
		(*str_ptr)++;
	}
	return (1);
}

char	*build_variable_name(const char **str_ptr, int *is_positional_param)
{
	t_str_builder	var_name_sb;
	char			*var_name;

	(*str_ptr)++;
	if (ft_isdigit(**str_ptr))
	{
		*is_positional_param = 1;
		sb_init(&var_name_sb);
		if (!extract_positional_param(str_ptr, &var_name_sb))
			return (NULL);
	}
	else
	{
		*is_positional_param = 0;
		sb_init(&var_name_sb);
		if (!extract_variable_name(str_ptr, &var_name_sb))
			return (NULL);
	}
	var_name = sb_to_string(&var_name_sb);
	sb_free(&var_name_sb);
	return (var_name);
}

int	process_variable_in_string(const char **ip, t_str_builder *sb, char **envp,
		int last_exit_status)
{
	char	*expanded_part;

	expanded_part = process_variable_expansion(ip, envp, last_exit_status);
	if (expanded_part)
	{
		if (!sb_append_str(sb, expanded_part))
		{
			free(expanded_part);
			return (0);
		}
		free(expanded_part);
	}
	return (1);
}

int	process_normal_character(const char **ip, t_str_builder *sb)
{
	if (!sb_append_char(sb, **ip))
		return (0);
	(*ip)++;
	return (1);
}
