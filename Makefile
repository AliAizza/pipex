# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaizza <aaizza@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 01:21:26 by aaizza            #+#    #+#              #
#    Updated: 2022/02/20 20:22:54 by aaizza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC= get_next_line.c get_next_line_utils.c path.c pipex.c split.c utils.c

NAME= pipex

CC= gcc

FLAGS= -Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${SRC}
			${CC} ${SRC} ${FLAGS} -o ${NAME}

clean:
			rm -f ${NAME}

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re