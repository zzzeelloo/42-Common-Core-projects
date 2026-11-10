/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_2_command_processor_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:38:36 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 19:38:42 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

t_parse_element	*parse_and_validate_input(char *user_input)
{
	t_parse_element	*list;

	list = tokenize_command_line(user_input);
	if (!list)
		return (NULL);
	if (!validate_syntax(list))
	{
		cleanup_element_list(list);
		return (NULL);
	}
	return (list);
}

char	**expand_and_convert_elements(t_parse_element *list, char **envp)
{
	t_parse_element	*expanded_elements;
	char			**array_all_token;

	expanded_elements = process_variable_expansions(list, envp, g_exit_status);
	cleanup_element_list(list);
	if (!expanded_elements)
		return (NULL);
	array_all_token = convert_elements_to_string_array(expanded_elements);
	cleanup_element_list(expanded_elements);
	return (array_all_token);
}
