/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:31:04 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 17:45:43 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/utils.h"

int	parse_whitespace_and_sign(char *str, int *i, int *sign)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
			|| str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	return (*i);
}

int	parse_digits_and_validate(char *str, int *i, int *start, int *len)
{
	int	j;

	if (!str[*i])
		return (0);
	*start = *i;
	j = *i;
	while (str[j] && ft_isdigit(str[j]))
		j++;
	*len = j - *start;
	if (!*len)
		return (0);
	while (str[j] && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n'
			|| str[j] == '\r' || str[j] == '\v' || str[j] == '\f'))
		j++;
	if (str[j])
		return (0);
	return (j);
}

static void	remove_leading_zeros(char *str, int *start, int *len)
{
	while (*len > 1 && str[*start] == '0')
	{
		(*start)++;
		(*len)--;
	}
}

static int	check_long_long_bounds(char *str, int start, int len, int sign)
{
	if (len > 19)
		return (0);
	if (len == 19)
	{
		if (sign == -1)
		{
			if (ft_strcmp(str + start, "9223372036854775808") > 0)
				return (0);
		}
		else
		{
			if (ft_strcmp(str + start, "9223372036854775807") > 0)
				return (0);
		}
	}
	return (1);
}

int	check_long_long_limits(char *str, int start, int len, int sign)
{
	remove_leading_zeros(str, &start, &len);
	return (check_long_long_bounds(str, start, len, sign));
}
