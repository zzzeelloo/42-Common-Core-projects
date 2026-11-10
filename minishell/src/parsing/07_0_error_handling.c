/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_0_error_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:51:25 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 16:51:25 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	report_syntax_error_detail(const char *message, const char *detail)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)message, STDERR_FILENO);
	if (detail)
	{
		ft_putstr_fd(" `", STDERR_FILENO);
		ft_putstr_fd((char *)detail, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	g_exit_status = 2;
}
