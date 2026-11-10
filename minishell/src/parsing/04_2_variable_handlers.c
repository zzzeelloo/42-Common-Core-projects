/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_2_variable_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:37:59 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 17:59:39 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../libft/libft.h"

static char	*handle_exit_status(const char **str_ptr, char **envp,
		int last_exit_status)
{
	(*str_ptr)++;
	(*str_ptr)++;
	return (get_env_var_value("?", envp, last_exit_status));
}

static char	*handle_braced_variable(const char **str_ptr, char **envp,
		int last_exit_status)
{
	const char	*start;
	char		*var_name;
	char		*var_value;

	(*str_ptr)++;
	(*str_ptr)++;
	start = *str_ptr;
	while (**str_ptr && **str_ptr != '}')
		(*str_ptr)++;
	if (**str_ptr == '}')
	{
		var_name = ft_substr(start, 0, *str_ptr - start);
		if (!var_name)
			return (NULL);
		(*str_ptr)++;
		var_value = get_env_var_value(var_name, envp, last_exit_status);
		free(var_name);
		return (var_value);
	}
	else
		return (ft_strdup("$"));
}

static char	*handle_basic_variable(const char **str_ptr, char **envp,
		int last_exit_status)
{
	char	*var_name;
	char	*var_value;
	int		is_positional_param;

	var_name = build_variable_name(str_ptr, &is_positional_param);
	if (!var_name)
		return (NULL);
	if (is_positional_param)
	{
		free(var_name);
		return (ft_strdup(""));
	}
	var_value = get_env_var_value(var_name, envp, last_exit_status);
	free(var_name);
	return (var_value);
}

char	*process_variable_expansion(const char **str_ptr, char **envp,
		int last_exit_status)
{
	if (**str_ptr != '$')
		return (NULL);
	if (*(*str_ptr + 1) == '?')
		return (handle_exit_status(str_ptr, envp, last_exit_status));
	if (*(*str_ptr + 1) == '{')
		return (handle_braced_variable(str_ptr, envp, last_exit_status));
	return (handle_basic_variable(str_ptr, envp, last_exit_status));
}

int	should_expand_variable(const char *ip, t_quote quote_type)
{
	if (*ip != '$')
		return (0);
	if (quote_type == Q_SINGLE)
		return (0);
	if (is_valid_var_char(*(ip + 1)) || *(ip + 1) == '?' || *(ip + 1) == '{')
		return (1);
	return (0);
}
