/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:58:55 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 17:58:55 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include "struct.h"

extern int	g_exit_status;

// =============================================================================
// 01 - FILE OPERATIONS

void			open_infile(t_exec *exec, char *infile);
void			open_outfile(t_exec *exec, char *outfile, int mode);
void			open_outfile_utils(t_exec *exec, char *outfile, int mode);

int				check_parent_directory_exists(char *filepath);

// =============================================================================
// 02 - MEMORY MANAGEMENT & CLEANUP

void			free_split(char **arr);
void			free_triple(char ***triple);

void			free_pipex(t_exec *exec, int status, char *str, char *str2);
void			free_pipex_no_exit(t_exec *exec, int status, char *str,
					char *str2);
void			free_exec(t_exec *exec, int status, char *str, char *str2);

void			cleanup_global_resources(t_exec *exec);

void			ft_message(char *str, char *str2);
void			free_redir_tables(t_exec *exec);
void			free_exec_groups(t_exec *exec);
void			free_pipex_resources(t_exec *exec);
void			cleanup_pipex_complete(t_exec *exec);

// =============================================================================
// 03 - FILE DESCRIPTOR MANAGEMENT

void			cleanup_all_open_fds(void);
void			cleanup_exec_fds(t_exec *exec);

// =============================================================================
// 04 - SIGNAL HANDLING

void			signals_monitoring(void);
void			child_signals_monitoring(void);

// =============================================================================
// 05 - ENVIRONMENT MANAGEMENT

int				is_valid_var_name(const char *name);
char			*create_env_string(char *name, char *value);
int				count_env_vars(char **envp);
int				find_env_index(char **envp, const char *name);
char			*find_env_value(char **envp, const char *name);
char			**copy_basic_env(char **envp);

int				replace_env_var(char ***env_ptr, int index, char *name,
					char *value);

int				add_new_env_var(char ***env_ptr, char *name, char *value);

int				set_env_var_global(char ***env_ptr, char *name, char *value);
int				unset_env_var_global(char ***env_ptr, char *name);

int				my_setenv(char *name, char *value);
int				my_unsetenv(char *name);

// =============================================================================
// 06 - CD UTILITIES

char			*get_env_value(char *key);
char			*get_env_value_from_envp(char *key, char **envp);
int				set_env_value(char *key, char *value);

// =============================================================================
// 07 - EXPORT UTILITIES

int				is_valid_identifier(char *str);
void			print_export_var_with_value(char *env_var, char *equals_pos);
void			print_export_var_without_value(char *env_var);
void			print_export_vars(char **envp);
void			print_export_error(char *arg, char *key);

#endif