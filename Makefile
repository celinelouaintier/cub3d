.SILENT:

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g3 -I./includes -I./minilibx -D BONUS=${BONUS}

LIBFT = libft.a
LIBPATH = lib

MLX = libmlx.a
MLXPATH = minilibx

PROG		= cub3D

SRCS_DIR	= srcs/
SRCS		= main.c init/init_fd.c init/init_game.c init/init_tex.c utils.c game_loop.c player.c check.c raycasting.c textures.c minimap.c sprite.c init/init_enemies.c controls.c list.c enemy.c clean.c
SRC 		= ${addprefix ${SRCS_DIR}, ${SRCS}} 

OBJS_DIR	= objs/
OBJS		= $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRC))

BONUS		= 0

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
					@echo "\033[34mCompiling $<..."
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

all: 		minilibx ${PROG}

${PROG}:	${OBJS}
					@echo "\033[33m----Compiling lib----"
					@if [ -f $(MLXPATH)/Makefile ]; then make -s -C $(MLXPATH); fi
					@if [ -f $(LIBPATH)/Makefile ]; then make -s -C $(LIBPATH); fi
					@echo "\n"
					$(CC) $(CFLAGS) ${OBJS} $(LIBPATH)/$(LIBFT) $(MLXPATH/$MLX) -o ${PROG} -L./minilibx -lmlx -lXext -lX11 -lm
					@echo "\033[32m Cub3d Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

bonus:
					make -s all BONUS=1

clean:
					@if [ -d ./lib ]; then make -s clean -C ./lib; fi
					@if [ -d ./minilibx ]; then make -s clean -C ./minilibx; fi
					@ ${RM} $(OBJS_DIR)/*.o
					@ ${RM} -rf $(OBJS_DIR)
					rm -f ${OBJS}

fclean: 	clean
					@if [ -f ./lib/Makefile ]; then make -s fclean -C ./lib; fi
					rm -f ${PROG}
					@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re:			fclean all

minilibx:
					@echo "\033[34mDownloading minilibx...\033[0m"
					wget -q https://cdn.intra.42.fr/document/document/26097/minilibx-linux.tgz
					tar -xf minilibx-linux.tgz
					rm -rf minilibx-linux.tgz
					mv minilibx-linux minilibx
					@echo "\033[32mDownload complete!\033[0m"

party:
					@printf "\033c"
					@echo "\n\033[35m♪┏(・o･)┛♪"
					@sleep 1
					@printf "\033c"
					@echo "\033[1;33m♪┗(・o･)┓♪"
					@sleep 1
					@printf "\033c"
					@echo "\n\033[36m♪┏(・o･)┛♪"
					@sleep 1
					@printf "\033c"
					@echo "\033[34m♪┗(・o･)┓♪\n"

.PHONY: all clean fclean re libft party