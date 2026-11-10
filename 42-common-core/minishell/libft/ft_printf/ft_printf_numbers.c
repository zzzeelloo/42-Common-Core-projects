/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:09:37 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 20:50:18 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_putnbr(int n)
{
	long	nb;
	int		len;

	len = 0;
	nb = n;
	if (nb < 0)
	{
		len += write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
	{
		len += ft_printf_putnbr(nb / 10);
		len += ft_printf_putnbr(nb % 10);
	}
	else
	{
		nb = nb + '0';
		len += write(1, &nb, 1);
	}
	return (len);
}

int	ft_printf_putnbr_u(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
	{
		len += ft_printf_putnbr_u(n / 10);
		len += ft_printf_putnbr_u(n % 10);
	}
	else
	{
		n = n + '0';
		len += write(1, &n, 1);
	}
	return (len);
}

static int	ft_printf_base_called(unsigned int n, char *base,
		unsigned int base_len)
{
	int	len;

	len = 0;
	if (n >= base_len)
		len += ft_printf_base_called(n / base_len, base, base_len);
	len += write(1, &base[n % base_len], 1);
	return (len);
}

int	ft_printf_base(unsigned int nbr, char *base)
{
	return (ft_printf_base_called(nbr, base, ft_printf_strlen(base)));
}
