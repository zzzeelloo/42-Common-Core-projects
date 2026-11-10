/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_2_word_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:29:12 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:29:20 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	parse_unquoted_chars(const char **line_ptr, t_str_builder *sb, int *status)
{
	while (**line_ptr && char_is_word_start(**line_ptr)
		&& !char_is_operator_start(**line_ptr) && **line_ptr != '\''
		&& **line_ptr != '"')
	{
		if (!sb_append_char(sb, **line_ptr))
		{
			*status = 0;
			return (0);
		}
		(*line_ptr)++;
	}
	return (1);
}

int	should_keep_fragment(char *fragment_content,
		t_text_fragment **fragments_head, const char **line_ptr)
{
	if (ft_strlen(fragment_content) > 0)
		return (1);
	if (*fragments_head != NULL && (*fragments_head)->content != NULL)
		return (1);
	if (*line_ptr && (**line_ptr == '\'' || **line_ptr == '"'))
		return (1);
	return (0);
}

int	create_and_add_fragment(char *fragment_content,
		t_text_fragment **fragments_head, int *status)
{
	t_text_fragment	*new_fragment;

	new_fragment = create_text_fragment(fragment_content, QUOTE_NONE);
	if (!new_fragment)
	{
		free(fragment_content);
		*status = 0;
		return (0);
	}
	add_fragment(fragments_head, new_fragment);
	return (1);
}
