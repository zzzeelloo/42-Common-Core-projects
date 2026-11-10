/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:55:42 by anpetit           #+#    #+#             */
/*   Updated: 2024/11/26 17:57:25 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	if (s2[0] == '\0')
		return ((char *)s1);
	i = 0;
	while (s1[i] && i < len)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s1[i + j] == s2[j] && (i + j) < len)
			{
				j++;
				if (s2[j] == '\0')
					return ((char *)&s1[i]);
				if (s1[i + j] != s2[j])
					break ;
			}
		}
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>

int	main(void)
{
	const char *str1 = "dazd azd azd zerg erthg oazfjj";
	const char *str2 = "zerg";

	printf("Resultat: %s\n\n", ft_strnstr(str1, str2, 30));
}*/
