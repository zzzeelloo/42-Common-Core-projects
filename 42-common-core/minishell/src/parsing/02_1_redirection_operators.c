/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_1_redirection_operators.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:31:59 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 17:09:41 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	process_input_redir_operator(const char **line_ptr, t_parse_element **head)
{
	if (*(*line_ptr + 1) == '<')
	{
		(*line_ptr) += 2;
		return (add_operator_element(head, ft_strdup("<<"),
				ELEM_HEREDOC_REDIR));
	}
	else
	{
		(*line_ptr)++;
		return (add_operator_element(head, ft_strdup("<"), ELEM_INPUT_REDIR));
	}
}

int	process_output_redir_operator(const char **line_ptr, t_parse_element **head)
{
	if (*(*line_ptr + 1) == '>')
	{
		(*line_ptr) += 2;
		return (add_operator_element(head, ft_strdup(">>"), ELEM_APPEND_REDIR));
	}
	else
	{
		(*line_ptr)++;
		return (add_operator_element(head, ft_strdup(">"), ELEM_OUTPUT_REDIR));
	}
}

int	add_operator_element(t_parse_element **head, char *operator,
		t_element_type type)
{
	if (!operator)
		return (0);
	if (!add_element_to_list(head,
			(t_element_params){operator, type, QUOTE_NONE, NULL}))
	{
		free(operator);
		return (0);
	}
	return (1);
}
