NAME = cub3d

OBJ_DIR = obj

SRC_DIR = src/

MAP_DIR = font/

SRCS = 	${SRC_DIR}main.c \
		${SRC_DIR}${MAP_DIR}font.c\
		${SRC_DIR}${MAP_DIR}font_public.c\
		${SRC_DIR}${MAP_DIR}font_init.c\
		${SRC_DIR}${MAP_DIR}font_init_helper.c\
		${SRC_DIR}${MAP_DIR}font_write.c\
		${SRC_DIR}${MAP_DIR}image_edit.c\
		# ${SRC_DIR}${MAP_DIR}check_if_helper.c \
		# ${SRC_DIR}${MAP_DIR}check_if.c \
		# ${SRC_DIR}${MAP_DIR}general_helper.c \
		# ${SRC_DIR}${MAP_DIR}general_helper2.c \
		# ${SRC_DIR}${MAP_DIR}map_check.c \
		# ${SRC_DIR}${MAP_DIR}map_public.c \
		# ${SRC_DIR}${MAP_DIR}map_valid_helper.c \
		# ${SRC_DIR}${MAP_DIR}map_valid_helper2.c \
		# ${SRC_DIR}${MAP_DIR}map_valid.c \
		# ${SRC_DIR}${MAP_DIR}map.c \
# SRCS = 	${SRC_DIR}main.c \
# 		${SRC_DIR}${FONT_DIR}font.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

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

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: libft/src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ./libft --no-print-directory fclean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re