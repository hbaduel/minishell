NAME = minishell

SRC = src/main.c src/signal.c\
src/builtin/cd.c src/builtin/choosebuiltin.c src/builtin/echo.c src/builtin/env.c src/builtin/export.c src/builtin/printexport.c src/builtin/pwd.c src/builtin/unset.c \
src/command/execcmd.c src/command/heredoc.c src/command/readterminal.c src/command/path.c\
src/parsing/cut.c src/parsing/editline.c src/parsing/envp.c src/parsing/parsecmd.c src/parsing/parseredir.c src/parsing/parsing.c src/parsing/token.c src/parsing/checkline.c\
src/utils/free.c src/utils/ft_itoa.c src/utils/ft_split.c src/utils/utils.c src/utils/utils2.c

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
