/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_0_command_processor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:28:47 by zcherif           #+#    #+#             */
/*   Updated: 2025/09/12 17:52:22 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/utils.h"

int	setup_pipeline_groups(t_exec *exec, char **array_all_token)
{
	split_pipeline_groups(exec, array_all_token);
	if (!exec->groups)
	{
		free_exec(exec, 0, NULL, NULL);
		return (-1);
	}
	return (0);
}

int	count_groups(t_exec *exec)
{
	int	group_count;

	group_count = 0;
	while (exec->groups && exec->groups[group_count])
		group_count++;
	return (group_count);
}

static void	execute_based_on_group_count(t_exec *exec, int group_count,
		char ***env_ptr)
{
	if (group_count == 1)
		handle_single_command(exec, env_ptr);
	else if (group_count > 1)
		handle_pipeline(exec, group_count, env_ptr);
	else
		handle_empty_group_redirections(exec, env_ptr);
}

static int	prepare_command_execution(char *user_input, char ***env_ptr,
		t_exec *exec, char ***array_all_token)
{
	t_parse_element	*list;

	list = parse_and_validate_input(user_input);
	if (!list)
		return (-1);
	*array_all_token = expand_and_convert_elements(list, *env_ptr);
	if (!*array_all_token)
		return (-1);
	if (has_variable_assignment(*array_all_token))
	{
		process_variable_assignments(*array_all_token, env_ptr);
		free_split(*array_all_token);
		return (-1);
	}
	if (setup_pipeline_groups(exec, *array_all_token) == -1)
	{
		free_split(*array_all_token);
		return (-1);
	}
	return (0);
}

void	process_command_line(char *user_input, char ***env_ptr)
{
	char	**array_all_token;
	t_exec	exec;
	int		group_count;

	if (prepare_command_execution(user_input, env_ptr, &exec, &array_all_token)
		== -1)
		return ;
	free_split(array_all_token);
	array_all_token = NULL;
	group_count = count_groups(&exec);
	execute_based_on_group_count(&exec, group_count, env_ptr);
	free_exec(&exec, -1, NULL, NULL);
}
