NAME = minishell

SRC = main.c utils.c heredoc.c redir.c pipe.c utils2.c utils3.c quotes.c parsing.c utils3.c quotes.c builtin/pwd.c builtin/echo.c

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
