/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:00:07 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/10 17:01:56 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include <readline/readline.h>
#include <readline/history.h>

extern int	g_exit_status;

static void	child_sigint(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		g_exit_status = 130;
		write(2, "\n", 1);
	}
}

static void	child_sigquit(int signal)
{
	(void)signal;
	g_exit_status = 131;
	write(2, "Quit (core dumped)\n", 19);
	exit(131);
}

static void	manage_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals_monitoring(void)
{
	signal(SIGINT, manage_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals_monitoring(void)
{
	signal(SIGINT, child_sigint);
	signal(SIGQUIT, child_sigquit);
	signal(SIGPIPE, SIG_IGN);
}
