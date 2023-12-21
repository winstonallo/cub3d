NAME = cub3d

OBJ_DIR = obj

SRC_DIR = src/

RAY_DIR = raycaster/

MAP_DIR = map/

LIBFT_FLAGS = -L./libft -lft

FLAGS = -framework OpenGL -framework AppKit -I./minilibx-mac -L./minilibx-mac -lmlx

X11_FLAGS = -L/usr/X11/lib -lXext -lX11

STANDARD = /

SRCS = 	${SRC_DIR}main.c \
		${SRC_DIR}${RAY_DIR}raycast.c \
		${SRC_DIR}${RAY_DIR}init_game.c \
		${SRC_DIR}${RAY_DIR}drawing_utils.c \
		${SRC_DIR}${RAY_DIR}initialize.c \
		${SRC_DIR}${RAY_DIR}mlx_utils.c \
		${SRC_DIR}${RAY_DIR}events.c \
		${SRC_DIR}${RAY_DIR}minimap.c \
		${SRC_DIR}${RAY_DIR}raycasting_utils.c \
		${SRC_DIR}${RAY_DIR}math_utils.c \
		${SRC_DIR}${RAY_DIR}texture_utils.c \
		${SRC_DIR}${MAP_DIR}check_if_helper.c \
		${SRC_DIR}${MAP_DIR}general_helper.c \
		${SRC_DIR}${MAP_DIR}general_helper2.c \
		${SRC_DIR}${MAP_DIR}check_if.c \
		${SRC_DIR}${MAP_DIR}map_check.c \
		${SRC_DIR}${MAP_DIR}map_public.c \
		${SRC_DIR}${MAP_DIR}map_valid_helper.c \
		${SRC_DIR}${MAP_DIR}map_valid_helper2.c \
		${SRC_DIR}${MAP_DIR}map_valid.c \
		${SRC_DIR}${MAP_DIR}map.c \

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -g


RM = rm -rf

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	@$(MAKE) -C ./libft --no-print-directory
	@$(MAKE) -C ./minilibx-mac --no-print-directory
	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(OBJS) $(LIBFT_OBJS) -o $(NAME) $(FLAGS) $(X11_FLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(RAY_DIR)
	mkdir -p $(OBJ_DIR)/$(MAP_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ./libft --no-print-directory fclean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re