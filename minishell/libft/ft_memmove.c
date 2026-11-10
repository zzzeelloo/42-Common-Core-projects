/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:19:45 by anpetit           #+#    #+#             */
/*   Updated: 2024/11/26 17:22:49 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*source;
	unsigned char		*destination;
	size_t				i;

	if (n == 0)
		return (dest);
	if (!dest && !src)
		return (NULL);
	source = (const unsigned char *)(src);
	destination = (unsigned char *)(dest);
	if (dest < src)
	{
		i = -1;
		while (++i < n)
			destination[i] = source[i];
	}
	else
	{
		i = n + 1;
		while (--i > 0)
			destination[i - 1] = source[i - 1];
	}
	return (dest);
}
