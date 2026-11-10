/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:59:39 by anpetit           #+#    #+#             */
/*   Updated: 2024/11/27 15:27:32 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int n)
{
	int		len;
	long	nb;

	len = 0;
	nb = n;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa_recursive(int n, char *str, int *i)
{
	long	nb;

	nb = n;
	if (nb < 0)
		nb = -nb;
	if (nb > 9)
		ft_itoa_recursive(nb / 10, str, i);
	str[(*i)++] = nb % 10 + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		len;

	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
		str[i++] = '-';
	ft_itoa_recursive(n, str, &i);
	str[i] = '\0';
	return (str);
}
//#include <stdio.h>
//
//int	main(void)
//{
//	char    *result;
//
//	result = ft_itoa(-10004);
//
//	printf("%s", result);
//}
