#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BLACK  "\e[1;30m"
# define RED  "\e[1;31m"
# define GREEN  "\e[1;32m"
# define YELLOW  "\e[1;33m"
# define BLUE  "\e[1;34m"
# define PURPLE  "\e[1;35m"
# define WHITE  "\e[1;37m"
# define MAX_HISTORY_SIZE 100


void	ft_exiterror(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_readfd(int fd);
int		ft_strcmp(char *s1, char *s2);

#endif
