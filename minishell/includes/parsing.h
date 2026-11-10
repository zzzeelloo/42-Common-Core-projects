/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:58:48 by anpetit           #+#    #+#             */
/*   Updated: 2025/09/11 17:58:48 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "utils.h"

extern int	g_exit_status;

// =============================================================================
// 01 - LEXICAL & TOKENIZATION

t_parse_element	*tokenize_command_line(const char *input_line);

int				char_is_space(char c);
int				char_is_word_start(char c);
int				char_is_operator_start(char c);

int				process_word_element(const char **line_ptr,
					t_parse_element **head);
int				process_quoted_fragment(const char **line_ptr,
					t_text_fragment **fragments_head, int *status);
int				process_unquoted_fragment(const char **line_ptr,
					t_text_fragment **fragments_head, int *status);

char			*extract_quoted_content_new(const char **line_ptr,
					char quote_char, int *status);
int				create_and_add_fragment(char *fragment_content,
					t_text_fragment **fragments_head, int *status);
int				should_keep_fragment(char *fragment_content,
					t_text_fragment **fragments_head, const char **line_ptr);
int				handle_escaped_char(const char **line_ptr, t_str_builder *sb,
					int *status);
int				parse_unquoted_chars(const char **line_ptr, t_str_builder *sb,
					int *status);

void			cleanup_fragments(t_text_fragment *fragments_head);

// =============================================================================
// 02 - OPERATOR PROCESSING

int				process_operator_element(const char **line_ptr,
					t_parse_element **head);
int				add_operator_element(t_parse_element **head, char *operator,
					t_element_type type);

int				process_input_redir_operator(const char **line_ptr,
					t_parse_element **head);
int				process_output_redir_operator(const char **line_ptr,
					t_parse_element **head);

// =============================================================================
// 03 - SYNTAX VALIDATION

int				validate_syntax(t_parse_element *elements);

int				check_start_operator(t_parse_element *current);
int				check_consecutive_elements(t_parse_element *elements);
int				check_end_operator(t_parse_element *current);

int				is_invalid_pipe_sequence(t_element_type first,
					t_element_type second);
int				is_invalid_redirection_sequence(t_element_type first,
					t_element_type second);
int				is_invalid_operator_sequence(t_element_type first,
					t_element_type second);

char			*get_token_string(t_element_type kind);
void			report_invalid_sequence_error(t_element_type first,
					t_element_type second);
void			report_syntax_error_detail(const char *message,
					const char *detail);

// =============================================================================
// 04 - VARIABLE EXPANSION

char			*expand_variables_in_str(const char *input_str,
					t_quote quote_type, char **envp, int last_exit_status);
t_parse_element	*process_variable_expansions(t_parse_element *input_elements,
					char **environment, int shell_exit_code);

char			*process_element_by_context(t_parse_element *current,
					t_parse_element *previous, char **environment,
					int exit_code);
int				add_processed_element(t_parse_element **processed_list,
					char *processed_text, t_element_type type);
char			*process_word_element_variable(t_parse_element *element,
					char **environment, int shell_exit_code);
char			*process_operator_element_var(t_parse_element *element);
char			*process_word_element_no_expansion(t_parse_element *element);

char			*get_env_var_value(const char *var_name, char **envp,
					int last_exit_status);
int				is_valid_var_char(char c);

int				extract_positional_param(const char **str_ptr,
					t_str_builder *var_name_sb);
int				extract_variable_name(const char **str_ptr,
					t_str_builder *var_name_sb);
char			*build_variable_name(const char **str_ptr,
					int *is_positional_param);
int				process_variable_in_string(const char **ip, t_str_builder *sb,
					char **envp, int last_exit_status);
int				process_normal_character(const char **ip, t_str_builder *sb);
int				should_expand_variable(const char *ip, t_quote quote_type);
char			*process_variable_expansion(const char **str_ptr, char **envp,
					int last_exit_status);

// =============================================================================
// 05 - VARIABLE ASSIGNMENT

int				is_variable_assignment(const char *str);
int				process_variable_assignment(const char *assignment,
					char ***env_ptr);
int				has_variable_assignment(char **tokens);
int				process_variable_assignments(char **tokens, char ***env_ptr);

// =============================================================================
// 06 - STRING BUILDER

void			sb_init(t_str_builder *sb);
int				sb_append_char(t_str_builder *sb, char c);
int				sb_append_str(t_str_builder *sb, const char *s);
char			*sb_to_string(t_str_builder *sb);
void			sb_free(t_str_builder *sb);

// =============================================================================
// 07 - ELEMENT & FRAGMENT

int				add_element_to_list(t_parse_element **head,
					t_element_params params);
void			cleanup_element_list(t_parse_element *list);

t_text_fragment	*create_text_fragment(char *content, t_quote_style style);
void			add_fragment(t_text_fragment **head,
					t_text_fragment *new_fragment);

// =============================================================================
// 08 - FINAL

char			**convert_elements_to_string_array(
					t_parse_element *element_list);

void			free_char_array(char **array);
void			cleanup_string_array(char **string_array, size_t index);
size_t			count_elements(t_parse_element *element_list);

#endif