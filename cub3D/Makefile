NAME    := cub3D
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
OS      := $(shell uname)
OBJ_DIR := obj

ifeq ($(OS), Darwin)
	MLX_DIR   := minilibx/macos
	MLX_LIB   := $(MLX_DIR)/libmlx.a
	MLX_FLAGS := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR   := minilibx/linux
	MLX_LIB   := $(MLX_DIR)/libmlx.a
	MLX_FLAGS := -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lbsd
endif

INCLUDES := -I$(MLX_DIR) -Iincludes

SRC_CONF := src/config/error_handler.c \
	src/config/free_src.c \
	src/config/initial_config_settings.c \
	src/config/initial_settings.c

SRC_EV := src/events/closing.c \
	src/events/keys.c \
	src/events/make_move.c \
	src/events/moves.c

SRC_PARS := src/parsing/buffer.c \
	src/parsing/colors.c \
	src/parsing/colors_utils.c \
	src/parsing/grid_padded.c \
	src/parsing/parse_file.c \
	src/parsing/parse_file_utils.c \
	src/parsing/parse_map.c \
	src/parsing/player_data.c \
	src/parsing/textures_data.c \
	src/parsing/textures_path.c \
	src/parsing/validate_map_empty_line.c \
	src/parsing/validate_map.c

SRC_REND := src/rendering/background.c \
	src/rendering/dda.c \
	src/rendering/render.c \
	src/rendering/texturized_wall.c \
	src/rendering/walls.c

SRC_UT := src/utils/free_array.c \
	src/utils/ft_atoi.c \
	src/utils/ft_isdigit.c \
	src/utils/ft_isspace.c \
	src/utils/ft_split.c \
	src/utils/ft_strcmp.c \
	src/utils/ft_strdup.c \
	src/utils/ft_strjoin.c \
	src/utils/ft_strlcpy.c \
	src/utils/ft_strlen.c \
	src/utils/ft_strncmp.c \
	src/utils/ft_substr.c \
	src/utils/get_next_line.c

SRC  := main.c
SRCS := $(SRC) $(SRC_UT) $(SRC_REND) $(SRC_PARS) $(SRC_EV) $(SRC_CONF)
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS := $(OBJS:.o=.d)
RM   := rm -f

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	-$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)