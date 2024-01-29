NAME = cub3d

OBJ_DIR = obj

SRC_DIR = src/

RAY_DIR = raycaster/

MAP_DIR = map/

STANDARD = /

SRCS = 	${SRC_DIR}main.c \
		${SRC_DIR}${RAY_DIR}raycast.c \
		${SRC_DIR}${RAY_DIR}scaling.c \
		${SRC_DIR}${RAY_DIR}drawing_utils.c \
		${SRC_DIR}${RAY_DIR}initialize.c \
		${SRC_DIR}${RAY_DIR}mlx_utils.c \
		${SRC_DIR}${RAY_DIR}events.c \
		${SRC_DIR}${RAY_DIR}minimap.c \
		${SRC_DIR}${RAY_DIR}raycasting_utils.c \
		${SRC_DIR}${RAY_DIR}math_utils.c \
		${SRC_DIR}${RAY_DIR}exit.c \
		${SRC_DIR}${RAY_DIR}rays_init.c \
		${SRC_DIR}${RAY_DIR}line_utils.c \
		${SRC_DIR}${RAY_DIR}textures.c \
		${SRC_DIR}${RAY_DIR}errors.c \
		${SRC_DIR}${MAP_DIR}check_if_helper.c \
		${SRC_DIR}${MAP_DIR}general_helper.c \
		${SRC_DIR}${MAP_DIR}general_helper2.c \
		${SRC_DIR}${MAP_DIR}general_helper3.c \
		${SRC_DIR}${MAP_DIR}check_if.c \
		${SRC_DIR}${MAP_DIR}map_check.c \
		${SRC_DIR}${MAP_DIR}map_public.c \
		${SRC_DIR}${MAP_DIR}map_valid_helper.c \
		${SRC_DIR}${MAP_DIR}map_valid_helper2.c \
		${SRC_DIR}${MAP_DIR}map_valid_helper3.c \
		${SRC_DIR}${MAP_DIR}map_valid.c \
		${SRC_DIR}${MAP_DIR}map.c \
		${SRC_DIR}${MAP_DIR}rgb_checker_utils.c \

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -g 

LDFLAGS = -Lminilibx-linux -L ./libft -lmlx -lXext -lX11 -lm -lft

RM = rm -rf

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	@$(MAKE) -C ./libft --no-print-directory
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)$(STANDARD)$(RAY_DIR)
	mkdir -p $(OBJ_DIR)$(STANDARD)$(MAP_DIR)

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
