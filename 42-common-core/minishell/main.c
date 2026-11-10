/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:07:46 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 18:21:12 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

int	g_exit_status = 0;

static void	init_minishell(void)
{
	signals_monitoring();
	ft_printf("Minishell started. Type 'exit' to quit.\n");
}

static int	handle_user_input(char **user_input, char ***env_copy)
{
	*user_input = readline("$> ");
	if (!*user_input)
	{
		ft_printf("\nexit\n");
		return (0);
	}
	if (ft_strlen(*user_input) == 0)
	{
		free(*user_input);
		return (1);
	}
	add_history(*user_input);
	if (ft_strcmp(*user_input, "exit") == 0)
	{
		free(*user_input);
		return (0);
	}
	process_command_line(*user_input, env_copy);
	free(*user_input);
	cleanup_all_open_fds();
	return (1);
}

static void	main_loop(char **envp)
{
	char	*user_input;
	char	**env_copy;

	env_copy = copy_basic_env(envp);
	if (!env_copy)
		return ;
	while (1)
	{
		if (!handle_user_input(&user_input, &env_copy))
			break ;
	}
	ft_freesplit(env_copy);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	init_minishell();
	main_loop(envp);
	cleanup_all_open_fds();
	return (g_exit_status);
}
