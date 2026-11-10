/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_0_syntax_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:32:31 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 18:47:05 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_invalid_pipe_sequence(t_element_type first, t_element_type second)
{
	if (first == ELEM_PIPE && second == ELEM_PIPE)
		return (1);
	if ((first == ELEM_OUTPUT_REDIR || first == ELEM_APPEND_REDIR
			|| first == ELEM_INPUT_REDIR || first == ELEM_HEREDOC_REDIR)
		&& second == ELEM_PIPE)
		return (1);
	return (0);
}

int	is_invalid_redirection_sequence(t_element_type first, t_element_type second)
{
	if ((first == ELEM_OUTPUT_REDIR || first == ELEM_APPEND_REDIR)
		&& (second == ELEM_INPUT_REDIR || second == ELEM_HEREDOC_REDIR))
		return (1);
	if ((first == ELEM_INPUT_REDIR || first == ELEM_HEREDOC_REDIR)
		&& (second == ELEM_OUTPUT_REDIR || second == ELEM_APPEND_REDIR))
		return (1);
	if ((first == ELEM_OUTPUT_REDIR || first == ELEM_APPEND_REDIR)
		&& (second == ELEM_OUTPUT_REDIR || second == ELEM_APPEND_REDIR))
		return (1);
	if ((first == ELEM_INPUT_REDIR || first == ELEM_HEREDOC_REDIR)
		&& (second == ELEM_INPUT_REDIR || second == ELEM_HEREDOC_REDIR))
		return (1);
	return (0);
}

int	is_invalid_operator_sequence(t_element_type first, t_element_type second)
{
	if (is_invalid_pipe_sequence(first, second))
		return (1);
	if (is_invalid_redirection_sequence(first, second))
		return (1);
	return (0);
}

char	*get_token_string(t_element_type type)
{
	if (type == ELEM_PIPE)
		return ("|");
	else if (type == ELEM_INPUT_REDIR)
		return ("<");
	else if (type == ELEM_OUTPUT_REDIR)
		return (">");
	else if (type == ELEM_APPEND_REDIR)
		return (">>");
	else if (type == ELEM_HEREDOC_REDIR)
		return ("<<");
	else
		return ("newline");
}

int	validate_syntax(t_parse_element *elements)
{
	t_parse_element	*current;

	if (!elements)
		return (1);
	if (!check_start_operator(elements))
		return (0);
	if (!check_consecutive_elements(elements))
		return (0);
	current = elements;
	while (current && current->next)
		current = current->next;
	if (!check_end_operator(current))
		return (0);
	return (1);
}
