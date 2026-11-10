/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:33:29 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 20:36:45 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	builtin_pwd(char **args)
{
	char	*actual_pwd;

	(void)args;
	actual_pwd = getcwd(NULL, 0);
	if (actual_pwd)
	{
		ft_putstr_fd(actual_pwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(actual_pwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
