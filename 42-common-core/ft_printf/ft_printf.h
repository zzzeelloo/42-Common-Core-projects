/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:54:43 by zcherif           #+#    #+#             */
/*   Updated: 2023/10/24 12:25:39 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int				ft_printf(char const *str, ...);
int				ft_pholder(char const *str, va_list args, int i, int j);
int				ft_putchar(char c);
int				ft_putstr(char *s);
int				ft_putnbr(long n);
unsigned int	ft_unsignedint(unsigned int n);
int				ft_hex(unsigned long hnbr, char str);

#endif
