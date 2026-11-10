/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_0_variable_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:33:46 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:35:06 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../libft/libft.h"

char	*expand_variables_in_str(const char *input_str, t_quote quote_type,
		char **envp, int last_exit_status)
{
	t_str_builder	sb;
	const char		*ip;
	char			*result;

	if (!input_str)
		return (NULL);
	sb_init(&sb);
	ip = input_str;
	while (*ip)
	{
		if (should_expand_variable(ip, quote_type))
		{
			if (!process_variable_in_string(&ip, &sb, envp, last_exit_status))
				return (sb_free(&sb), NULL);
		}
		else if (!process_normal_character(&ip, &sb))
			return (sb_free(&sb), NULL);
	}
	result = sb_to_string(&sb);
	sb_free(&sb);
	return (result);
}
