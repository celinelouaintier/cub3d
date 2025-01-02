.SILENT:

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -I./includes -I./minilibx

LIBFT = libft.a
LIBPATH = lib

MLX = libmlx.a
MLXPATH = minilibx

SRCS_DIR	= srcs/

PROG		= cub3d

SRCS		= main.c init/init_fd.c utils.c map.c player.c check.c
SRC 		= ${addprefix ${SRCS_DIR}, ${SRCS}}
OBJS 		= ${SRC:.c=.o}

%.o: %.c
					@echo "\033[34mCompiling $<..."
					$(CC) $(CFLAGS) -c $< -o $@

all: 		${PROG}

${PROG}:	${OBJS}
					@echo "\033[33m----Compiling lib----"
					@make -s -C $(LIBPATH)
					@make -s -C $(MLXPATH)
					@echo "\n"
					$(CC) $(CFLAGS) ${OBJS} $(LIBPATH)/$(LIBFT) $(MLXPATH/$MLX) -o ${PROG} -L./minilibx -lmlx -lXext -lX11 -lm
					@echo "\033[32m Cub3d Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

clean:
					make -s clean -C ./lib
					make -s clean -C ./minilibx
					rm -f ${OBJS}

fclean: 	clean
					make -s fclean -C ./lib
					make -s -C ./minilibx clean
					rm -f ${PROG}
					@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re:			fclean all

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