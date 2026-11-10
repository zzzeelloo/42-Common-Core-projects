/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angus <angus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:30:23 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 17:47:21 by angus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parsing.h"
#include "../../includes/utils.h"

static char	*get_current_directory(void)
{
	char	cwd[4096];
	char	*old_pwd;

	if (getcwd(cwd, sizeof(cwd)))
		old_pwd = ft_strdup(cwd);
	else
		old_pwd = ft_strdup("/");
	if (!old_pwd)
		ft_putstr_fd("cd: memory allocation failed\n", STDERR_FILENO);
	return (old_pwd);
}

static char	*target_directory(char **args, char *old_pwd, char ***env_ptr)
{
	char	*home;

	if (!args[1] || ft_strlen(args[1]) == 0)
	{
		home = find_env_value(*env_ptr, "HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			free(old_pwd);
			return (NULL);
		}
		return (home);
	}
	return (args[1]);
}

static void	print_cd_error(char *target_dir)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(target_dir, STDERR_FILENO);
	if (errno == ENOENT)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else if (errno == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": Cannot change directory\n", STDERR_FILENO);
}

static void	update_pwd(char *old_pwd, char ***env_ptr)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env_var_global(env_ptr, "PWD", cwd);
		set_env_var_global(env_ptr, "OLDPWD", old_pwd);
	}
}

int	builtin_cd(char **args, char ***env_ptr)
{
	char	*target_dir;
	char	*old_pwd;
	int		result;

	old_pwd = get_current_directory();
	if (!old_pwd)
		return (1);
	target_dir = target_directory(args, old_pwd, env_ptr);
	if (!target_dir)
		return (1);
	result = chdir(target_dir);
	if (result != 0)
	{
		print_cd_error(target_dir);
		free(old_pwd);
		return (1);
	}
	update_pwd(old_pwd, env_ptr);
	free(old_pwd);
	return (0);
}
