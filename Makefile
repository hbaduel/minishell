NAME = minishell

SRC = main.c utils.c redirections.c

OBJS = ${SRC:%.c=%.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror

LFLAGS = -lreadline

RM = rm -rf

${NAME}: ${OBJS}
	${CC} ${FLAGS} -o ${NAME} ${OBJS} ${LFLAGS}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.phony: all clean fclean re
