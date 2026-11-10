/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:45:15 by anpetit           #+#    #+#             */
/*   Updated: 2025/07/17 15:33:49 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_str(char **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	is_in_charset(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

int	count_word(char const *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_in_charset(str[i], charset))
			i++;
		if (str[i] && !is_in_charset(str[i], charset))
		{
			count++;
			while (str[i] && !is_in_charset(str[i], charset))
				i++;
		}
	}
	return (count);
}

char	*wordup(char const *str, char charset)
{
	int		i;
	int		len;
	char	*word;

	len = 0;
	while (str[len] && !is_in_charset(str[len], charset))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**result;

	result = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_in_charset(s[i], c))
			i++;
		if (s[i] && !is_in_charset(s[i], c))
		{
			result[j] = wordup(&s[i], c);
			if (!result[j])
				return (free_str(result, j), NULL);
			j++;
			while (s[i] && !is_in_charset(s[i], c))
				i++;
		}
	}
	result[j] = 0;
	return (result);
}
