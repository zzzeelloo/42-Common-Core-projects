/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_0_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:51:37 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 15:02:41 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static size_t	count_words_in_text(char *text)
{
	char	**words;
	size_t	count;

	if (!ft_strchr(text, ' ') || ft_strchr(text, '='))
		return (1);
	words = ft_split(text, ' ');
	if (!words)
		return (1);
	count = 0;
	while (words[count])
		count++;
	ft_freesplit(words);
	return (count);
}

size_t	count_elements(t_parse_element *element_list)
{
	size_t			element_count;
	t_parse_element	*current;

	element_count = 0;
	current = element_list;
	while (current)
	{
		if (current->text)
			element_count += count_words_in_text(current->text);
		current = current->next;
	}
	return (element_count);
}

void	free_char_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	cleanup_string_array(char **string_array, size_t index)
{
	size_t	j;

	j = 0;
	while (j < index)
	{
		free(string_array[j]);
		j++;
	}
	free(string_array);
}
