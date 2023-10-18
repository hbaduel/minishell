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
# include <signal.h>

# define BLACK  "\e[1;30m"
# define RED  "\e[1;31m"
# define GREEN  "\e[1;32m"
# define YELLOW  "\e[1;33m"
# define BLUE  "\e[1;34m"
# define PURPLE  "\e[1;35m"
# define WHITE  "\e[1;37m"
# define NOTHING    0
# define CMD        1
# define PIPE       2
# define INFILE     3
# define OUTFILE    4
# define HEREDOC    5
# define APPEND     6
# define INCOMPLET  7
# define OUTCOMPLET 8
# define HDCOMPLET  9
# define APPENDCOMP 10


typedef struct s_parse {
    int     type;           /*pour identifier le type de commande*/
    char    **args;         /*pour stocker les arguments de la commande*/
    struct s_parse  *next;
    struct s_parse  *previous;
    struct s_data   *data;
}       t_parse;

typedef struct	s_data
{
	int	infilefd;
	int	outfilefd;
	int	ncmd;
    int pipe_detector;
    t_parse *parse;
}				t_data;

void	ft_exiterror(char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_heredoc(char *limiter, t_data *data);
void	ft_openfile(char *file, t_data *data, int which);
void	ft_pipe(t_data *data, t_parse *parsing, char **envp);
void	ft_execcmd(t_data *data, char **cmd, char **envp, int outfd);
void    ft_print_tokens(t_parse *parse);
void	ft_pwd(char **cmd);
void	ft_echo(char **cmd);
void	ft_check_quote(char *str);
t_parse	*ft_parse(char *, t_data *data);
char	*ft_strjoin(char *s1, char *s2, int dofree);
char	*ft_readfd(int fd);
char	*ft_cmdpath(char *cmd, char **envp);
char	*ft_strtok(char *str, char delim);
char	*ft_strdup(char *s);
char    *ft_cut_terminal(char *terminal, char *token);
char    *ft_check_filename(char *str);
char    *ft_add_space_before(char *str);
char    **ft_realloc(char **args, char *token);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strlcpy(char *dest, char *src, int size);

#endif
