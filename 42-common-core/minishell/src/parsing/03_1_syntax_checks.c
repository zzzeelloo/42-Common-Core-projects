/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_1_syntax_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:33:06 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 18:47:05 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	report_invalid_sequence_error(t_element_type first,
		t_element_type second)
{
	if (first == ELEM_PIPE && second == ELEM_PIPE)
		report_syntax_error_detail("syntax error near unexpected token", "|");
	else if (first == ELEM_APPEND_REDIR && second == ELEM_PIPE)
		report_syntax_error_detail("syntax error near unexpected token", "|");
	else if (first == ELEM_OUTPUT_REDIR && second == ELEM_PIPE)
		report_syntax_error_detail("syntax error near unexpected token", "|");
	else if (first == ELEM_INPUT_REDIR && second == ELEM_PIPE)
		report_syntax_error_detail("syntax error near unexpected token", "|");
	else if (first == ELEM_HEREDOC_REDIR && second == ELEM_PIPE)
		report_syntax_error_detail("syntax error near unexpected token", "|");
	else
		report_syntax_error_detail("syntax error near unexpected token",
			get_token_string(second));
}

int	check_start_operator(t_parse_element *current)
{
	if (current->type == ELEM_PIPE)
	{
		report_syntax_error_detail("syntax error near unexpected token",
			get_token_string(current->type));
		return (0);
	}
	return (1);
}

int	check_consecutive_elements(t_parse_element *elements)
{
	t_parse_element	*current;
	t_parse_element	*next;

	current = elements;
	while (current && current->next)
	{
		next = current->next;
		if (is_invalid_operator_sequence(current->type, next->type))
		{
			report_invalid_sequence_error(current->type, next->type);
			return (0);
		}
		current = next;
	}
	return (1);
}

int	check_end_operator(t_parse_element *current)
{
	if (current && (current->type == ELEM_PIPE
			|| current->type == ELEM_OUTPUT_REDIR
			|| current->type == ELEM_APPEND_REDIR
			|| current->type == ELEM_INPUT_REDIR
			|| current->type == ELEM_HEREDOC_REDIR))
	{
		report_syntax_error_detail("syntax error near unexpected token",
			"newline");
		return (0);
	}
	return (1);
}
