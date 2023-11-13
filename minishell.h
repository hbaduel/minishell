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
# define NOTHING	0
# define CMD		1
# define PIPE		2
# define INFILE		3
# define OUTFILE	4
# define HEREDOC	5
# define APPEND		6
# define INCOMPLET	7
# define OUTCOMPLET	8
# define HDCOMPLET	9
# define APPENDCOMP	10


typedef struct s_parse {
    int             type;           /*pour identifier le type de commande*/
    char            **args;         /*pour stocker les arguments de la commande*/
    struct s_parse  *next;
    struct s_parse  *previous;
    struct s_data   *data;
}       t_parse;

typedef struct	s_data
{
	char	**envp;
	int 	infilefd;
	int 	outfilefd;
	int 	ncmd;
	int		status;
	int		pipe_detector;
	t_parse	*parse;
}		t_data;


void	ft_putstr_fd(char *str, int fd);
void	ft_heredoc(char *limiter, char *next, t_data *data);
void	ft_pipe(t_data *data, t_parse *parsing);
void	ft_execcmd(char **cmd, char **envp, int outfd);
void	ft_pwd(t_data *data, int outfd, char **cmd);
void	ft_echo(t_data *data, char **cmd, int outfd);
void	ft_freedoubletab(char **tab);
void	ft_env(t_data *data, int outfd, char **cmd);
void	ft_unset(t_data *data, char **cmd);
void	ft_export(t_data *data, char **cmd, int outfd);
void    ft_putenv(char *nexttoken, char *env, int *j);
void	ft_free_all(t_parse *parse);
t_parse	*ft_parse(char *, t_data *data);
char	*ft_strjoin(char *s1, char *s2, int dofree);
char	*ft_cmdpath(char *cmd, char **envp);
char	*ft_strtok(t_data *data, char *str);
char	*ft_strdup(char *s);
char	*ft_cut_terminal(char *terminal, char *token);
char	*ft_add_space_before(char *str);
char	*ft_getenv(char **envp, int status, char *name, int *k);
char	*ft_strstr(char *haystack, char *needle);
char	*ft_strcpy(char *dest, char *src);
char	*ft_tokennoquote(t_data *data, char *str);
char	*ft_getenvname(char *str);
char	*ft_itoa(int n);
char	*ft_tokennoquote(t_data *data, char *str);
char	**ft_realloc(char **args, char *token);
char	**ft_split(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
int 	ft_openfile(char *file, t_data *data, int which);
int 	ft_cmdbuiltin(t_data *data, int outfd, char **cmd);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_check_quote(char *str);
int		ft_checkequal(char *env);

#endif
