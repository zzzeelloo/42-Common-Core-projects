/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_3_word_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/XX XX:XX:XX by angus             #+#    #+#             */
/*   Updated: 2025/01/XX XX:XX:XX by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	process_quoted_fragment(const char **line_ptr,
		t_text_fragment **fragments_head, int *status)
{
	char			quote_char;
	char			*fragment_content;
	t_text_fragment	*new_fragment;
	t_quote_style	quote_type;

	quote_char = **line_ptr;
	fragment_content = extract_quoted_content_new(line_ptr, quote_char, status);
	if (*status <= 0 || !fragment_content)
		return (0);
	if (quote_char == '"')
		quote_type = QUOTE_DOUBLE;
	else
		quote_type = QUOTE_SINGLE;
	new_fragment = create_text_fragment(fragment_content, quote_type);
	if (!new_fragment)
	{
		*status = 0;
		return (0);
	}
	add_fragment(fragments_head, new_fragment);
	return (1);
}

int	process_unquoted_fragment(const char **line_ptr,
		t_text_fragment **fragments_head, int *status)
{
	t_str_builder	sb_unquoted;
	char			*fragment_content;

	sb_init(&sb_unquoted);
	if (!parse_unquoted_chars(line_ptr, &sb_unquoted, status))
	{
		sb_free(&sb_unquoted);
		return (0);
	}
	fragment_content = sb_to_string(&sb_unquoted);
	sb_free(&sb_unquoted);
	if (!fragment_content)
	{
		*status = 0;
		return (0);
	}
	if (should_keep_fragment(fragment_content, fragments_head, line_ptr))
	{
		if (!create_and_add_fragment(fragment_content, fragments_head, status))
			return (0);
	}
	else
		free(fragment_content);
	return (1);
}

int	process_word_element(const char **line_ptr, t_parse_element **head)
{
	t_text_fragment	*fragments_head;
	int				status;

	fragments_head = NULL;
	status = 1;
	while (**line_ptr && char_is_word_start(**line_ptr)
		&& !char_is_operator_start(**line_ptr))
	{
		if ((**line_ptr == '\'' || **line_ptr == '"')
			&& !process_quoted_fragment(line_ptr, &fragments_head, &status))
			break ;
		else if (!process_unquoted_fragment(line_ptr, &fragments_head, &status))
			break ;
		if (status <= 0)
		{
			cleanup_fragments(fragments_head);
			return (status);
		}
	}
	if (fragments_head && !add_element_to_list(head,
			(t_element_params){NULL, ELEM_WORD, QUOTE_NONE, fragments_head}))
		return (0);
	return (1);
}
