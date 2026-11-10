/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:44:23 by anpetit           #+#    #+#             */
/*   Updated: 2024/11/26 17:45:13 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	src_len;
	size_t	i;
	char	*dest;

	src_len = ft_strlen(s);
	dest = malloc(sizeof(char) * (src_len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
