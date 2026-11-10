/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_0_final_conversion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:46:17 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:46:17 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	should_split_word(char *text)
{
	if (!ft_strchr(text, ' '))
		return (0);
	if (ft_strchr(text, '='))
		return (0);
	return (1);
}

static int	add_words_to_array(char **array, char *text, size_t *index)
{
	char	**words;
	int		i;

	if (!should_split_word(text))
	{
		array[(*index)++] = ft_strdup(text);
		return (array[*index - 1] != NULL);
	}
	words = ft_split(text, ' ');
	if (!words)
		return (0);
	i = 0;
	while (words[i])
	{
		array[(*index)++] = ft_strdup(words[i]);
		if (!array[*index - 1])
		{
			ft_freesplit(words);
			return (0);
		}
		i++;
	}
	ft_freesplit(words);
	return (1);
}

static int	fill_string_array(char **string_array,
		t_parse_element *element_list)
{
	t_parse_element	*current;
	size_t			index;

	current = element_list;
	index = 0;
	while (current)
	{
		if (current->text)
		{
			if (!add_words_to_array(string_array, current->text, &index))
			{
				cleanup_string_array(string_array, index);
				return (0);
			}
		}
		current = current->next;
	}
	string_array[index] = NULL;
	return (1);
}

char	**convert_elements_to_string_array(t_parse_element *element_list)
{
	size_t		element_count;
	char		**string_array;

	if (!element_list)
	{
		string_array = malloc(sizeof(char *));
		if (!string_array)
			return (NULL);
		string_array[0] = NULL;
		return (string_array);
	}
	element_count = count_elements(element_list);
	string_array = malloc((element_count + 1) * sizeof(char *));
	if (!string_array)
		return (NULL);
	if (!fill_string_array(string_array, element_list))
	{
		free(string_array);
		return (NULL);
	}
	return (string_array);
}

t_text_fragment	*create_text_fragment(char *content, t_quote_style style)
{
	t_text_fragment	*fragment;

	fragment = malloc(sizeof(t_text_fragment));
	if (!fragment)
	{
		free(content);
		return (NULL);
	}
	fragment->content = content;
	fragment->style = style;
	fragment->next = NULL;
	return (fragment);
}
