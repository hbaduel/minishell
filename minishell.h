#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BLACK  "\e[1;30m"
# define RED  "\e[1;31m"
# define GREEN  "\e[1;32m"
# define YELLOW  "\e[1;33m"
# define BLUE  "\e[1;34m"
# define PURPLE  "\e[1;35m"
# define WHITE  "\e[1;37m"

typedef struct	s_data
{
	int	infilefd;
	int	outfilefd;
}				t_data;

void	ft_exiterror(char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_heredoc(char *limiter);
void	redir_input(char *file, t_data *data);
void	redir_output(char *file, t_data *data);
void	redir_append(char *file, t_data *data);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_readfd(int fd);
int		ft_strcmp(char *s1, char *s2);

#endif
