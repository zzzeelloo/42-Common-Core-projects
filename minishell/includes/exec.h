/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:58:40 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/12 18:24:53 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include "utils.h"

// =============================================================================
// 01 - COMMAND PROCESSING & MAIN ENTRY POINTS

void			process_command_line(char *user_input, char ***env_ptr);
t_parse_element	*parse_and_validate_input(char *user_input);
char			**expand_and_convert_elements(t_parse_element *list,
					char **envp);

void			handle_single_command(t_exec *exec, char ***env_ptr);
void			handle_pipeline(t_exec *exec, int group_count, char ***env_ptr);
void			handle_empty_group_redirections(t_exec *exec, char ***env_ptr);

// =============================================================================
// 02 - PIPELINE SETUP & MANAGEMENT

int				setup_pipeline_groups(t_exec *exec, char **array_all_token);
int				initialize_pipeline(t_exec *exec, int group_count, char **envp);
void			split_pipeline_groups(t_exec *exec, char **tokens);
void			pipex_init(t_exec *exec, char **envp);

int				count_groups(t_exec *exec);
int				count_pipes(char **tokens);
void			count_redirections(t_exec *exec, char **tokens);
void			init_exec(t_exec *exec);

void			setup_pipe_descriptors_first(t_exec *exec, int *pipe_fd,
					int group_count, int i);
void			setup_pipe_descriptors_last(t_exec *exec, int prev_pipe_read);
void			setup_pipe_descriptors_middle(t_exec *exec, int prev_pipe_read,
					int *pipe_fd);
void			setup_pipe_descriptors(t_exec *exec, int group_count,
					int prev_pipe_read, int *pipe_fd);

// =============================================================================
// 03 - GROUP SPLITTING & TOKEN PROCESSING

void			split_groups(t_exec *exec, char **tokens);
void			finalize_group(t_exec *exec);

void			is_notpipe(t_exec *exec, char **tokens);
void			is_outfile(t_exec *exec, char **tokens);
void			is_infile(t_exec *exec, char **tokens);
void			is_heredoc(t_exec *exec, char **tokens);
int				is_token(const char *tok, const char *s);

void			assign_outfile_redirection(t_exec *exec, char **tokens);
void			assign_infile_redirection(t_exec *exec, char **tokens);
void			assign_heredoc_redirection(t_exec *exec, char **tokens);

// =============================================================================
// 04 - SINGLE COMMAND EXECUTION

void			exec_one(t_exec *exec, char **cmd_args, char **envp);
int				setup_single_command_basic(t_exec *exec, char **envp);

void			setup_input_redirection_one(t_exec *exec);
void			setup_output_redirection_one(t_exec *exec);
void			handle_env_special_case(t_exec *exec);
void			handle_builtin_execution(t_exec *exec, char ***env_ptr);

// =============================================================================
// 05 - PROCESS EXECUTION & MANAGEMENT

void			execute_bonus_args(t_exec *exec, char **cmd_args, char **envp);
void			check_exec_file(t_exec *exec, char *cmd);
void			check_exec(t_exec *exec, char *cmd);
void			check_if_directory(t_exec *exec, char **cmd_args);
void			handle_execve_error(t_exec *exec);

int				contains_slash(const char *s);

// =============================================================================
// 06 - FILE OPERATIONS & REDIRECTIONS

int				open_files_for_single_command(t_exec *exec);
int				open_input_file_single(t_exec *exec);
int				open_output_file_single(t_exec *exec);
void			apply_redirections_for_builtin(t_exec *exec, int *saved_stdin,
					int *saved_stdout);
void			restore_original_fds(int saved_stdin, int saved_stdout);

void			open_files_for_pipeline(t_exec *exec, int group_count);
int				open_outfile_for_validation(t_exec *exec, char **tokens);

void			setup_redirections(t_exec *exec);

// =============================================================================
// 07 - CHILD PROCESS OPERATIONS

void			check_infile_access(t_exec *exec, int current_cmd);
void			open_infile_fd(t_exec *exec, int current_cmd);
void			check_outfile_directory(t_exec *exec, int current_cmd);
void			open_outfile_fd(t_exec *exec, int current_cmd);
void			handle_outfile_error(t_exec *exec, int current_cmd);

void			handle_infile_redirection(t_exec *exec, int current_cmd);
void			handle_outfile_redirection(t_exec *exec, int current_cmd);
void			open_files_for_current_command(t_exec *exec);
void			setup_input_redirection(t_exec *exec);
void			setup_output_redirection(t_exec *exec);

// =============================================================================
// 08 - HEREDOC PROCESSING

int				create_heredoc_pipe(const char *delimiter);
void			cleanup_heredoc(t_cmd_redir *cmd_redir);
void			cleanup_all_heredocs(t_exec *exec);
void			cleanup_previous_heredoc(t_exec *exec);
void			setup_new_heredoc(t_exec *exec, char **tokens);
int				check_delimiter(char *line, const char *delimiter,
					size_t delimiter_len);

// =============================================================================
// 09 - PIPELINE PROCESS MANAGEMENT

int				create_child_process(t_exec *exec, int i, char **envp);
int				handle_parent_pipes(int prev_pipe_read, int i, int group_count,
					int *pipe_fd);
int				create_pipe_for_command(int i, int group_count, int pipe_fd[2],
					int *pipe_created);
int				setup_pipeline_context(t_exec *exec, int i, int group_count,
					int prev_pipe_read);
int				process_single_command(t_exec *exec, char **envp);
int				process_pipeline_command(t_exec *exec, int i, int group_count,
					char **envp);
int				execute_pipeline_commands(t_exec *exec, int group_count,
					char **envp);

// =============================================================================
// 10 - BUILTIN COMMANDS

int				is_builtin(char *cmd);
int				execute_builtin(char **args, char ***env_ptr);
int				execute_builtin_with_exec(char **args, char ***env_ptr,
					t_exec *exec);

int				builtin_echo(char **args);
int				builtin_pwd(char **args);
int				builtin_env(char **args, char ***env_ptr);
int				builtin_cd(char **args, char ***env_ptr);
int				builtin_export(char **args, char ***env_ptr);
int				builtin_unset(char **args, char ***env_ptr);
int				builtin_exit(char **args);
int				builtin_exit_with_cleanup(char **args, t_exec *exec);

int				export_with_value(char *arg, char *equals_pos, char ***env_ptr);
int				export_without_value(char *arg, char ***env_ptr);
void			print_export_vars(char **envp);
void			print_export_error(char *arg, char *key);

int				parse_whitespace_and_sign(char *str, int *i, int *sign);
int				parse_digits_and_validate(char *str, int *i, int *start,
					int *len);
int				check_long_long_limits(char *str, int start, int len, int sign);

// =============================================================================
// 11 - CLEANUP & MEMORY MANAGEMENT

void			free_pipex(t_exec *exec, int status, char *str, char *str2);
void			free_exec(t_exec *exec, int status, char *str, char *str2);
void			cleanup_empty_group_resources(t_exec *exec);

void			cleanup_child_memory_for_execve(t_exec *exec);
void			cleanup_child_groups(t_exec *exec);
void			cleanup_child_redirs(t_exec *exec);
void			cleanup_child_memory_full(t_exec *exec);

void			cleanup_parent_fds(t_exec *exec, int group_count);
void			cleanup_pipes_on_error(int *pipe_fd, int prev_pipe_read,
					int pipe_created);
void			cleanup_created_processes(t_exec *exec, int up_to_index);
void			handle_pipe_creation_error(t_exec *exec, int i,
					int prev_pipe_read);
void			finalize_pipeline(t_exec *exec, int group_count);

// =============================================================================
// 12 - MEMORY ALLOCATION UTILITIES

char			***allocate_groups(int count);
char			**allocate_double(int count);

// =============================================================================
// 13 - ENVIRONMENT & INITIALIZATION

void			initialize_shell_environment(char **envp, char **av);

#endif