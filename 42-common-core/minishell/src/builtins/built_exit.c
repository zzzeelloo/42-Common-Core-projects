/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:31:04 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 18:45:39 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/utils.h"

int	parse_and_validate(char *str, int *start, int *len, int *sign)
{
	int	i;
	int	j;

	i = 0;
	*sign = 1;
	parse_whitespace_and_sign(str, &i, sign);
	if (!str[i])
		return (0);
	j = parse_digits_and_validate(str, &i, start, len);
	if (!j)
		return (0);
	return (1);
}

int	is_valid_number(char *str)
{
	int	start;
	int	len;
	int	sign;

	start = 0;
	len = 0;
	sign = 1;
	if (!str || !str[0])
		return (0);
	if (!parse_and_validate(str, &start, &len, &sign))
		return (0);
	return (check_long_long_limits(str, start, len, sign));
}

int	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	write(1, "exit\n", 5);
	if (args[1])
	{
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			exit(1);
		}
		if (!is_valid_number(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(255);
		}
		exit_code = ft_atoi(args[1]);
		exit_code = exit_code & 0xFF;
		exit(exit_code);
	}
	exit(exit_code);
}

static int	validate_exit_args(char **args, t_exec *exec)
{
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		cleanup_global_resources(exec);
		exit(1);
	}
	if (!is_valid_number(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		cleanup_global_resources(exec);
		exit(255);
	}
	return (ft_atoi(args[1]) & 0xFF);
}

int	builtin_exit_with_cleanup(char **args, t_exec *exec)
{
	int	exit_code;

	exit_code = 0;
	write(1, "exit\n", 5);
	if (args[1])
		exit_code = validate_exit_args(args, exec);
	cleanup_global_resources(exec);
	exit(exit_code);
}
