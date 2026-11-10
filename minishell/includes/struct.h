/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:58:22 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 18:47:05 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_str_builder
{
	char					*str;
	size_t					len;
}							t_str_builder;

typedef enum e_element_type
{
	ELEM_WORD,
	ELEM_PIPE,
	ELEM_INPUT_REDIR,
	ELEM_OUTPUT_REDIR,
	ELEM_APPEND_REDIR,
	ELEM_HEREDOC_REDIR
}							t_element_type;

typedef enum e_quote_style
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}							t_quote_style;

typedef struct s_text_fragment
{
	char					*content;
	t_quote_style			style;
	struct s_text_fragment	*next;
}							t_text_fragment;

typedef struct s_parse_element
{
	char					*text;
	t_element_type			type;
	t_quote_style			quote_mode;
	t_text_fragment			*fragments;
	struct s_parse_element	*next;
}							t_parse_element;

typedef struct s_element_params
{
	char					*value;
	t_element_type			type;
	t_quote_style			style;
	t_text_fragment			*fragments;
}							t_element_params;

typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}							t_quote;

typedef struct s_pipex
{
	pid_t					*pids;
	char					*cmd;
	char					**cmd_args;
	char					**paths;
	int						infile;
	int						outfile;
	char					*infile_name;
	char					*outfile_name;
	int						fd[2];
	int						status;
	int						here_doc;
	int						cmd_nbr;
	int						i;
	int						envp;
	int						prev_pipe_read;
	int						pipe_fd[2];
}							t_pipex;

typedef struct s_cmd_redir
{
	char					*infile;
	char					*outfile;
	int						append;
	int						infile_fd;
	int						outfile_fd;
	char					*heredoc_delimiter;
	int						heredoc_fd;
	int						is_heredoc;
}							t_cmd_redir;

typedef struct s_exec
{
	int						count;
	char					***groups;
	char					**cmds;
	int						i;
	int						ncmd;
	int						ng;
	char					**infile_name;
	char					**outfile_name;
	int						*append;
	int						infile;
	int						outfile;
	char					**group;
	int						redir;
	int						redir_in;
	int						redir_out;
	int						current_redir_in;
	int						current_redir_out;
	int						total_commands;
	t_cmd_redir				*cmd_redirs;
	t_pipex					pipex;
}							t_exec;

extern int					g_exit_status;

#endif