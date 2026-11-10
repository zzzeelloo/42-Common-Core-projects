/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_0_operator_processing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:30:59 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 18:47:05 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	process_pipe_operator(const char **line_ptr, t_parse_element **head)
{
	if (*(*line_ptr + 1) == '|')
	{
		report_syntax_error_detail("syntax error near unexpected token", "||");
		return (-1);
	}
	(*line_ptr)++;
	return (add_operator_element(head, ft_strdup("|"), ELEM_PIPE));
}

int	process_operator_element(const char **line_ptr, t_parse_element **head)
{
	if (**line_ptr == '|')
		return (process_pipe_operator(line_ptr, head));
	else if (**line_ptr == '<')
		return (process_input_redir_operator(line_ptr, head));
	else if (**line_ptr == '>')
		return (process_output_redir_operator(line_ptr, head));
	else
		return (0);
}
