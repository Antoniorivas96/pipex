SRCS	= ft_pipex.c pipex_utils.c
NAME	= pipex
CC	= gcc
FLAGS	= -Wall -Werror -Wextra -fsanitize=address -g
RM	= rm -f
LIBFT	= libft.a
OBJ = $(SRCS:.c=.o)

all: ${NAME}

${NAME}: ${LIBFT} ${OBJ}
	${CC} ${FLAGS} -o ${NAME} ${SRCS} ${LIBFT}

bonus: runlibft norm
	${CC} ${FLAGS} -o ${NAME} -I ${INCS} ${LIBFT}

${OBJ}: ${SRCS}
	$(CC) $(FLAGS) -c $(SRCS)

clean:
	${RM} ${NAME} ${OBJ} ${LIBFT}
	make -C libft clean

fclean: clean
	make -C libft fclean

re: fclean all

${LIBFT}:
	make -C libft
	mv libft/libft.a libft.a

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS} 
	norminette -R CheckDefine ${INCS} pipex.h pipex_bonus.h

.PHONY: all re clean fclean norm
