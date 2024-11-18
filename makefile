NAME 		= battle_snake

TEST_NAME 	= small_test

CC 			= gcc

FLAGS 		= -Wall -Werror -Wextra

SRC_DIR 	= src

OBJ_DIR 	= obj

SRC 		= main.c utils.c pixeling.c init.c handle_keys.c loop.c end_game.c

SRC			:= $(addprefix $(SRC_DIR)/, $(SRC))

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_DIR = mlx-linux
	MLX_LIB = -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S), Darwin) # macOS
	MLX_DIR = mlx_macos
	MLX_LIB = -framework OpenGL -framework AppKit
endif


${OBJ_DIR}/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	${CC} ${FLAGS} -I/usr/include -I${MLX_DIR} -O3 -c $< -o $@

${NAME}: ${OBJ}
	make -s -C ${MLX_DIR}
	${CC} ${OBJ} ./${MLX_DIR}/libmlx.a ${MLX_LIB} -o ${NAME}

all:	${NAME}

clean:
	make clean -s -C ${MLX_DIR}
	rm -rf ${OBJ_DIR}

fclean:	clean
	rm -f ${NAME}

re: fclean all