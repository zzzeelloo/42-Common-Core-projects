/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_2_variable_processor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:39:39 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:39:39 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	*process_fragment(t_text_fragment *fragment, char **environment,
		int shell_exit_code)
{
	t_quote	quote_type;

	if (fragment->style != QUOTE_SINGLE)
	{
		if (fragment->style == QUOTE_DOUBLE)
			quote_type = Q_DOUBLE;
		else
			quote_type = Q_NONE;
		return (expand_variables_in_str(fragment->content, quote_type,
				environment, shell_exit_code));
	}
	return (ft_strdup(fragment->content));
}

char	*process_word_element_variable(t_parse_element *element,
		char **environment, int shell_exit_code)
{
	t_str_builder	word_buffer;
	t_text_fragment	*current_fragment;
	char			*processed_content;
	char			*final_word;

	sb_init(&word_buffer);
	current_fragment = element->fragments;
	while (current_fragment)
	{
		processed_content = process_fragment(current_fragment, environment,
				shell_exit_code);
		if (!processed_content || !sb_append_str(&word_buffer,
				processed_content))
		{
			free(processed_content);
			sb_free(&word_buffer);
			return (NULL);
		}
		free(processed_content);
		current_fragment = current_fragment->next;
	}
	final_word = sb_to_string(&word_buffer);
	sb_free(&word_buffer);
	return (final_word);
}

char	*process_operator_element_var(t_parse_element *element)
{
	return (ft_strdup(element->text));
}

char	*process_word_element_no_expansion(t_parse_element *element)
{
	t_str_builder	word_buffer;
	t_text_fragment	*current_fragment;
	char			*final_word;

	sb_init(&word_buffer);
	current_fragment = element->fragments;
	while (current_fragment)
	{
		if (!sb_append_str(&word_buffer, current_fragment->content))
		{
			sb_free(&word_buffer);
			return (NULL);
		}
		current_fragment = current_fragment->next;
	}
	final_word = sb_to_string(&word_buffer);
	sb_free(&word_buffer);
	return (final_word);
}

t_parse_element	*process_variable_expansions(t_parse_element *input_elements,
		char **environment, int shell_exit_code)
{
	t_parse_element	*current_element;
	t_parse_element	*previous_element;
	t_parse_element	*processed_list;
	char			*processed_text;

	processed_list = NULL;
	current_element = input_elements;
	previous_element = NULL;
	while (current_element)
	{
		processed_text = process_element_by_context(current_element,
				previous_element, environment, shell_exit_code);
		if (!add_processed_element(&processed_list, processed_text,
				current_element->type))
		{
			cleanup_element_list(processed_list);
			return (NULL);
		}
		previous_element = current_element;
		current_element = current_element->next;
	}
	return (processed_list);
}
