/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_1_element_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:47:16 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:50:58 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	add_fragment(t_text_fragment **head, t_text_fragment *new_fragment)
{
	t_text_fragment	*current;

	if (!*head)
	{
		*head = new_fragment;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_fragment;
}

static void	cleanup_fragments_on_error(t_text_fragment *fragments)
{
	t_text_fragment	*current_f;
	t_text_fragment	*next_f;

	current_f = fragments;
	while (current_f)
	{
		next_f = current_f->next;
		free(current_f->content);
		free(current_f);
		current_f = next_f;
	}
}

static void	insert_element_at_end(t_parse_element **head,
		t_parse_element *new_element)
{
	t_parse_element	*current;

	if (!*head)
	{
		*head = new_element;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_element;
}

int	add_element_to_list(t_parse_element **head, t_element_params params)
{
	t_parse_element	*new_element;

	new_element = malloc(sizeof(t_parse_element));
	if (!new_element)
	{
		cleanup_fragments_on_error(params.fragments);
		return (0);
	}
	new_element->text = params.value;
	new_element->type = params.type;
	new_element->quote_mode = params.style;
	new_element->fragments = params.fragments;
	new_element->next = NULL;
	insert_element_at_end(head, new_element);
	return (1);
}

void	cleanup_element_list(t_parse_element *list)
{
	t_parse_element	*current;
	t_parse_element	*next;
	t_text_fragment	*current_fragment;
	t_text_fragment	*next_fragment;

	current = list;
	while (current)
	{
		next = current->next;
		if (current->text)
			free(current->text);
		current_fragment = current->fragments;
		while (current_fragment)
		{
			next_fragment = current_fragment->next;
			free(current_fragment->content);
			free(current_fragment);
			current_fragment = next_fragment;
		}
		free(current);
		current = next;
	}
}
