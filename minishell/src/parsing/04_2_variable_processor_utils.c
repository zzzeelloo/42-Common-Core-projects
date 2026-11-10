/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_2_variable_processor_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:45:00 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 17:09:41 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	should_skip_expansion(t_parse_element *prev, t_parse_element *curr)
{
	return (prev && prev->type == ELEM_HEREDOC_REDIR
		&& curr->type == ELEM_WORD);
}

char	*process_element_by_context(t_parse_element *current,
		t_parse_element *previous, char **environment, int exit_code)
{
	if (should_skip_expansion(previous, current))
		return (process_word_element_no_expansion(current));
	else if (current->type == ELEM_WORD)
		return (process_word_element_variable(current, environment,
				exit_code));
	else
		return (process_operator_element_var(current));
}

int	add_processed_element(t_parse_element **processed_list,
		char *processed_text, t_element_type type)
{
	if (!processed_text)
		return (0);
	if (!add_element_to_list(processed_list,
			(t_element_params){processed_text, type, QUOTE_NONE, NULL}))
		return (0);
	return (1);
}
