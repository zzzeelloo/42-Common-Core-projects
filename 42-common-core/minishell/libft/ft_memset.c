/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:23:08 by anpetit           #+#    #+#             */
/*   Updated: 2024/11/26 17:29:08 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	caract;
	size_t			i;

	ptr = (unsigned char *)(s);
	caract = (unsigned char)(c);
	i = 0;
	while (i < n)
	{
		ptr[i] = caract;
		i++;
	}
	return (s);
}
