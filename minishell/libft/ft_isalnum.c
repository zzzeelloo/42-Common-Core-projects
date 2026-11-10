/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:14:16 by anpetit           #+#    #+#             */
/*   Updated: 2024/11/26 17:14:16 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || ((c >= 'A' && c <= 'Z') || (c >= 'a'
				&& c <= 'z')))
		return (1);
	else
		return (0);
}

/*#include <stdio.h>

int	main(void)
{
	int	c;

	c = 66;

	printf("%d", ft_isalnum(c));
}*/
