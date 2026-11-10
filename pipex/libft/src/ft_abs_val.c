/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:09:30 by zcherif           #+#    #+#             */
/*   Updated: 2024/01/23 11:40:47 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* abs_value returns absolute value of an input */
int	abs_value(int value)
{
	int	abs;

	abs = value;
	if (value < 0)
		abs = -value;
	return (abs);
}
