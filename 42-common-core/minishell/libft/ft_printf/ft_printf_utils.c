/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:46:17 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 20:16:57 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_putchar(const char c)
{
	return (write(1, &c, 1));
}

int	ft_printf_putstr(const char *c)
{
	if (!c)
		return (write(1, "(null)", 6));
	return (write(1, c, ft_printf_strlen(c)));
}

int	ft_printf_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_printf_hexa_len(unsigned long n, char *base)
{
	int	len;

	len = 0;
	if (n >= 16)
		len = ft_printf_hexa_len(n / 16, base);
	write(1, &base[n % 16], 1);
	return (len + 1);
}

int	ft_printf_putptr(void *ptr)
{
	unsigned long	addr;
	int				len;

	len = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	len = write(1, "0x", 2);
	addr = (unsigned long)ptr;
	len += ft_printf_hexa_len(addr, "0123456789abcdef");
	return (len);
}
