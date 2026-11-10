NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_ALL:%.c=%.o))
DEPS = $(OBJ:.o=.d)

SRC_EXEC =    src/exec/01_0_command_processor.c        \
              src/exec/01_0_command_processor_utils.c  \
            src/exec/01_1_pipeline_setup.c    		\
            src/exec/01_2_group_splitting.c         \
            src/exec/01_2_group_splitting_utils.c   \
            src/exec/01_3_pipeline_splitting.c      \
            src/exec/01_4_pipeline_splitting_utils.c \
            src/exec/02_0_child_process.c            \
            src/exec/02_1_child_file_ops.c           \
            src/exec/02_2_child_redirections.c       \
            src/exec/02_3_pipeline_process.c         \
            src/exec/02_3_pipeline_process_utils.c   \
            src/exec/03_0_single_execution.c         \
            src/exec/03_1_single_execution_redirections.c \
            src/exec/03_1_single_execution_setup.c    \
            src/exec/03_2_bonus_execution.c          \
            src/exec/03_3_bonus_execution_utils.c    \
            src/exec/03_4_pipeline_execution.c       \
            src/exec/04_0_file_redirections.c        \
            src/exec/04_1_file_redirections_utils.c  \
            src/exec/04_3_heredoc_processing.c       \
            src/exec/04_4_heredoc_utils.c            \
            src/exec/05_0_exec_cleanup.c             \
            src/exec/05_1_pipeline_cleanup.c         \
            src/exec/05_2_group_finalization.c       \
            src/exec/06_0_bonus_utils.c              \
            src/exec/06_1_bonus_utils_2.c            \
            src/exec/06_2_command_processor_utils.c  \
            src/builtins/builtin_integration.c      \
            src/builtins/built_echo.c               \
            src/builtins/built_pwd.c                \
            src/builtins/built_env.c                \
            src/builtins/built_cd.c                 \
            src/builtins/built_export.c             \
            src/builtins/built_export_utils.c       \
            src/builtins/built_export_print.c       \
            src/builtins/built_unset.c              \
            src/builtins/built_exit.c               \
            src/builtins/built_exit_utils.c         \

SRC_PARSING =	src/parsing/01_0_lexical_core.c			\
				src/parsing/01_1_lexical_utils.c		\
				src/parsing/01_2_word_processing.c		\
				src/parsing/01_3_word_element.c			\
				src/parsing/02_0_operator_processing.c	\
				src/parsing/02_1_redirection_operators.c	\
				src/parsing/03_0_syntax_validation.c		\
				src/parsing/03_1_syntax_checks.c			\
				src/parsing/04_0_variable_expansion.c		\
				src/parsing/04_1_variable_utilities.c	\
				src/parsing/04_2_variable_processor.c	\
				src/parsing/04_2_variable_processor_utils.c	\
				src/parsing/04_2_variable_handlers.c	\
				src/parsing/04_3_variable_assignment.c	\
				src/parsing/04_3_variable_processing.c	\
				src/parsing/05_0_string_builder.c		\
				src/parsing/05_1_quote_processing.c		\
				src/parsing/06_0_final_conversion.c		\
				src/parsing/06_1_element_management.c	\
				src/parsing/07_0_error_handling.c		\
				src/parsing/08_0_parsing_utils.c		\

SRC_UTILS =	src/utils/free_struct.c		\
		src/utils/free_struct_utils.c	\
		src/utils/open.c			\
		src/utils/ft_signal.c		\
		src/utils/fd_cleanup.c		\
		src/utils/directory_utils.c	\
		src/utils/env_setunset.c	\
		src/utils/env_operations.c	\
		src/utils/env_utils.c		\
		src/utils/cleanup_utils.c	\
		src/utils/message_utils.c	\



SRC_ALL = $(SRC_EXEC) $(SRC_UTILS) $(SRC_PARSING) main.c

GREEN=\033[0;32m
BLUE=\033[38;2;64;224;208m
RED=\033[0;91m
WHITE=\033[2;37m
NC=\033[0m

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: %.c Makefile libft/Makefile
	@echo "$(WHITE) mkdir -p $(dir $@) $(NC)"
	@mkdir -p $(dir $@)
	@echo "$(GREEN) $(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I$(LIBFT_DIR) $(NC)"
	@$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I$(LIBFT_DIR)

-include $(DEPS)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN) $(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft $(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline

$(OBJ_DIR):
	@echo "$(WHITE) mkdir -p $(OBJ_DIR) $(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

libft:
	make -C $(LIBFT_DIR)

clean:
	@echo "$(RED) rm -rf $(OBJ_DIR) $(NC)"
	@echo "$(RED) make -C $(LIBFT_DIR) clean $(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED) rm -f $(NAME) $(NC)"
	@echo "$(RED) make -C $(LIBFT_DIR) fclean $(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

re_bonus: fclean

.PHONY: all clean fclean re libft