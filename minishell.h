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
# define NOTHING    0
# define CMD        1
# define SEPARATEUR 2
# define INFILE     3
# define OUTFILE    4

typedef struct s_parse {
    int     type;           /*pour identifier le type de commande*/
    char    *other;
    char    **args;         /*pour stocker les arguments de la commande*/
    struct s_parse  *next;

}       t_parse;


void	ft_exiterror(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_readfd(int fd);
int		ft_strcmp(char *s1, char *s2);
t_parse     *ft_parse(char *terminal);
void    ft_free_parse(t_parse *parse);
int     ft_strlen(char *str);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char    *ft_strtok(char *str, char *delim);




#endif
