/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:41:21 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 20:47:32 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_format(char c, va_list args)
{
	if (c == '%')
		return (write(1, "%", 1));
	else if (c == 'c')
		return (ft_printf_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_printf_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_printf_putptr(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_printf_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_printf_putnbr_u(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_printf_base(va_arg(args, unsigned int),
				"0123456789abcdef"));
	else if (c == 'X')
		return (ft_printf_base(va_arg(args, unsigned int),
				"0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!format || write(1, 0, 0) == -1)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			count += ft_format(format[++i], args);
		else
			count += ft_printf_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
