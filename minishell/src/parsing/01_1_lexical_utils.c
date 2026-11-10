/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_1_lexical_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:28:38 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 18:47:05 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	char_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

int	char_is_word_start(char c)
{
	if (char_is_space(c) || c == '|' || c == '<' || c == '>' || c == '\0')
		return (0);
	return (1);
}

int	char_is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
