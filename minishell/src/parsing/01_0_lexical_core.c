/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_0_lexical_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:36:19 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:36:19 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	process_next_element(const char **input_line,
		t_parse_element **element_head)
{
	if (char_is_operator_start(**input_line))
		return (process_operator_element(input_line, element_head));
	else if (char_is_word_start(**input_line))
		return (process_word_element(input_line, element_head));
	else
	{
		report_syntax_error_detail("unexpected character",
			(char []){**input_line, 0});
		return (-1);
	}
}

t_parse_element	*tokenize_command_line(const char *input_line)
{
	t_parse_element	*element_head;
	int				parsing_status;

	element_head = NULL;
	parsing_status = 1;
	while (*input_line && parsing_status > 0)
	{
		while (*input_line && char_is_space(*input_line))
			input_line++;
		if (*input_line == '\0')
			break ;
		parsing_status = process_next_element((const char **)&input_line,
				&element_head);
	}
	if (parsing_status <= 0)
	{
		cleanup_element_list(element_head);
		return (NULL);
	}
	return (element_head);
}
