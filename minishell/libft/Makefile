NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
AR = ar rcs
RM = rm -rf

OBJ_DIR = obj

GREEN=\033[0;32m
BLUE=\033[38;2;64;224;208m
RED=\033[0;91m
WHITE=\033[2;37m
NC=\033[0m

DARK_YELLOW=\033[2;33m
YELLOW=\033[38;5;178m
DARK_GREEN=\033[38;5;22m
DARK_RED=\033[38;5;124m
BLACK=\033[0;30m
INV=\033[7m
FLASH=\033[5m

LIBFT_FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
       ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
       ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
       ft_toupper.c ft_tolower.c ft_strchr.c ft_substr.c \
       ft_strrchr.c ft_strncmp.c ft_strcmp.c ft_memchr.c ft_memcmp.c \
       ft_atoi.c ft_calloc.c ft_strdup.c ft_itoa.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
       ft_strmapi.c ft_striteri.c ft_strtrim.c ft_split.c ft_strjoin.c ft_strnstr.c ft_freesplit.c

PRINTF_FILES = ft_printf/ft_printf.c ft_printf/ft_printf_utils.c ft_printf/ft_printf_numbers.c

SRC_FILES = $(LIBFT_FILES) $(PRINTF_FILES) $(GNL_FILES)

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:%.c=%.o))
DEPS = $(OBJ:.o=.d)

all: $(OBJ_DIR) $(NAME)

	@echo "$(GREEN) LIBFT COMPILED!🎉$(NC)"

$(OBJ_DIR)/%.o: %.c Makefile
	@echo "$(WHITE) mkdir -p $(dir $@) $(NC)"
	@mkdir -p $(dir $@)
	@echo "$(DARK_GREEN) $(CC) $(CFLAGS) -MMD -MP -o $@ -c $<$(NC)"
	@$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<

-include $(DEPS)

$(NAME): $(OBJ)
	@echo "$(DARK_YELLOW) library created... $(NC)"
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR):
	@echo "$(WHITE) mkdir -p $(OBJ_DIR) $(NC)"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(DARK_RED) $(RM) $(OBJ_DIR) $(NC)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(DARK_RED) rm -f $(NAME) $(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
