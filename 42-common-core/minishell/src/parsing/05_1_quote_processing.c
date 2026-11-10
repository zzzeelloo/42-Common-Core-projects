/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_1_quote_processing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/XX XX:XX:XX by angus             #+#    #+#             */
/*   Updated: 2025/01/XX XX:XX:XX by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	process_quoted_content(const char **line_ptr, char quote_char,
		t_str_builder *sb)
{
	while (**line_ptr && **line_ptr != quote_char)
	{
		if (!sb_append_char(sb, **line_ptr))
			return (0);
		(*line_ptr)++;
	}
	return (1);
}

char	*extract_quoted_content_new(const char **line_ptr, char quote_char,
		int *status)
{
	t_str_builder	sb;
	char			*result;

	sb_init(&sb);
	(*line_ptr)++;
	*status = 1;
	if (!process_quoted_content(line_ptr, quote_char, &sb))
	{
		*status = 0;
		sb_free(&sb);
		return (NULL);
	}
	if (**line_ptr != quote_char)
	{
		sb_free(&sb);
		*status = -1;
		report_syntax_error_detail("unclosed quote", NULL);
		return (NULL);
	}
	(*line_ptr)++;
	result = sb_to_string(&sb);
	sb_free(&sb);
	if (!result)
		*status = 0;
	return (result);
}

void	cleanup_fragments(t_text_fragment *fragments_head)
{
	t_text_fragment	*current_f;
	t_text_fragment	*next_f;

	current_f = fragments_head;
	while (current_f)
	{
		next_f = current_f->next;
		free(current_f->content);
		free(current_f);
		current_f = next_f;
	}
}
