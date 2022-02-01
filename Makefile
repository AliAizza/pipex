SRC= pipex.c process.c split.c path.c

OBJ= {SRC:.c=.o}

NAME= pipex

CC= gcc

FLAGS= -Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${SRC}
			${CC} ${FLAGS} ${SRC} -o ${NAME}

clean:
			rm -f ${NAME}

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re