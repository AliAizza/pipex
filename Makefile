# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 01:21:26 by aaizza            #+#    #+#              #
#    Updated: 2022/02/18 01:29:16 by aaizza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC= get_next_line.c get_next_line_utils.c path.c pipex.c process.c split.c utils.c

OBJ= {SRC:.c=.o}

NAME= pipex

CC= gcc

FLAGS= -Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${SRC}
			${CC} ${SRC} -o ${NAME}

clean:
			rm -f ${NAME}

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re