# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 21:42:20 by zmoumen           #+#    #+#              #
#    Updated: 2023/08/11 01:04:35 by zmoumen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#~~~~~~~~~~~~~~[COMPILER]~~~~~~~~~~~~~~
CC = cc
CFLAGS = -Wall -Werror -Wextra -I./mlx42/include/MLX42 -I./libft -I. #-fsanitize=address -g3

NAME = cub3D
all: $(NAME)

SHELL = /bin/bash
.PHONY = all
#~~~~~~~~~~~~~~

#~~~~~~~~~~~~~~[SOURCE FILES]~~~~~~~~~~~~~~
SRC_MP_LDR = map_loader.c map_utils.c parse_matrix.c textures_utils/load_textures.c textures_utils/parse_textures.c

SRC = main.c $(addprefix map_loader/, $(SRC_MP_LDR))
#~~~~~~~~~~~~~~

#~~~~~~~~~~~~~~[COMPILER OBJ/DEP FILES]~~~~~~~~~~~~~~
OBJ_DIR = .mediators
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

DEP_DIR = .mediators
DEPS = $(addprefix $(DEP_DIR)/, $(SRC:.c=.d))
-include $(DEPS)
#~~~~~~~~~~~~~~

#~~~~~~~~~~~~~~[MLX AND ITS DEPS]~~~~~~~~~~~~~~
MLX = mlx42/build/libmlx42.a
MLX_CMAKE = mlx42/CMakeLists.txt
GLFW = $(shell brew info glfw | grep -E "Cellar" | cut -d " " -f 1 )/lib/libglfw.dylib

$(GLFW):
	@echo "📛  Missing glfw library"
	@echo "🛂  Install it with brew\n\n"
	@exit 1

$(MLX_CMAKE):
	@if [ -d mlx42 ]; then echo "🟠  MLX42 already cloned\n🛂  Call make re_mlx if folder is corrupted\n\n"; exit 1; fi
	@echo "📡  cloning mlx42"
	@git clone https://github.com/codam-coding-college/MLX42.git mlx42 --quiet
ifeq ($(MAKECMDGOALS), clone_mlx)
	@echo "✅  MLX42 Cloned"
endif

clone_mlx: $(MLX_CMAKE)

 $(MLX): $(GLFW)
	@if [ ! -d mlx42 ]; then echo "📛  MLX42 not cloned"; echo "🛂  Call make clone_mlx first"; exit 1; fi
	@echo "🏭🏗 Building MLX42"
	@cmake -Bmlx42/build -Hmlx42 > /dev/null
	@line_count=0; \
	while IFS= read -r line; do \
		((line_count++)); \
		echo "$$line"; \
	done < <(make -C mlx42/build); \
	if [ $(MAKECMDGOALS)"" != mlx ] && [ $(MAKECMDGOALS)"" != build_mlx ] ; then \
		for (( i=0; i<line_count; i++ )); do \
			tput cuu1; tput el; \
		done; \
	else \
		echo -n ""; \
	fi
	@echo "✅  MLX42 Built"

build_mlx: $(GLFW) $(MLX)

mlx: $(GLFW) $(MLX_CMAKE) $(MLX)

rm_mlx:
	@echo "🚮  Removing MLX42"
	@rm -rf mlx42

re_mlx: rm_mlx mlx

.PHONY += clone_mlx build_mlx mlx rm_mlx re_mlx
#~~~~~~~~~~~~~~

#~~~~~~~~~~~~~~[LIBFT]~~~~~~~~~~~~~~
LIBFT = libft/libft.a

$(LIBFT):
	@echo "🏭🏗 Building libft"
	@make -C libft > /dev/null

libft: $(LIBFT)

libft_clean:
	@echo "🚮  Cleaning libft"
	@make fclean -C libft > /dev/null

libft_re: libft_clean libft

.PHONY += libft libft_clean libft_re
#~~~~~~~~~~~~~~

#~~~~~~~~~~~~~~[CUB3D]~~~~~~~~~~~~~~
$(NAME): $(MLX_CMAKE) $(MLX) $(GLFW) $(LIBFT) $(OBJ)
	@echo "🏭🏗 Building executable"
	@echo "📦 linking with $(GLFW)"
	@$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) $(GLFW) -o $@
	@echo "✅🎮 Ready to Play"

$(OBJ_DIR)/%.o: %.c
	@echo "🏭🏗 Building $@"
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_DIR)/$*.d)
	@$(CC) $(CFLAGS) -I. -c  $< -o $@ -MMD -MF $(DEP_DIR)/$*.d
	@sleep 0.3;tput cuu1; tput el;
#~~~~~~~~~~~~~~


#~~~~~~~~~~~~~~[CLEANING]~~~~~~~~~~~~~~
clean:
	@echo "🚮  Cleaning folder from .o and .d files. Keeping executable and .a"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@make -C libft clean > /dev/null

fclean: clean rm_mlx libft_clean
	@echo "🚮  Removing executable and cleaning up libraries"
	@rm -rf $(NAME)

re_source_only: clean all

re: fclean all

.PHONY += clean fclean re
#~~~~~~~~~~~~~~
