/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:35:49 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/21 15:39:55 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <fcntl.h>

# define CMD		0
# define INFILE		1
# define OUTFILE	2
# define HEREDOC	3
# define APPEND		4
# define INCOMPLET	5
# define OUTCOMPLET	6
# define HDCOMPLET	7
# define APPENDCOMP	8

typedef struct s_parse {
	int				type;
	char			**args;
	struct s_parse	*next;
	struct s_parse	*previous;
	struct s_data	*data;
}		t_parse;

typedef struct s_data {
	char	*display;
	char	**envp;
	int		infilefd;
	int		outfilefd;
	int		ncmd;
	int		status;
	int		pipe_detector;
	t_parse	*parse;
}		t_data;

void	ft_readterminal(t_data *data);
void	ft_putstr_fd(char *str, int fd);
void	ft_pipe(t_data *data, t_parse *parsing, char *terminal);
void	ft_execcmd(char *term, char **cmd, t_data *data, int outfd);
void	ft_pwd(t_data *data, int outfd, char **cmd);
void	ft_echo(t_data *data, char **cmd, int outfd);
void	ft_freedoubletab(char **tab);
void	ft_env(t_data *data, int outfd, char **cmd);
void	ft_signalhandler(int sig);
void	ft_unset(t_data *data, char **cmd);
void	ft_export(t_data *data, char **cmd, int outfd);
void	ft_free_data(t_data *data);
void	ft_free_all(t_data *data, int outfd, char *terminal);
void	ft_putenv(char *nexttoken, char *env, int *j);
void	ft_printexport(int *status, char **sort, int outfd);
void	ft_freeline(t_data *data);
void	ft_addenvp(t_data *data, char *name, char *cmd);
void	ft_strncpy(char *dest, char *src, int n);
void	ft_cd(t_data *data, char **cmd);
t_parse	*ft_parse(char *terminal, t_data *data);
t_parse	*ft_newpipe(t_data *data, t_parse *current, char *token, char *line);
t_parse	*ft_parseredircomp(t_data *data, t_parse *current, char *token);
t_parse	*ft_newcmd(t_data *data, t_parse *current, char *token);
t_parse	*ft_realloc(t_parse *current, t_parse *previous, \
									char *token, int type);
t_parse	*ft_free_parse(t_parse *parse);
char	*ft_strtok(t_data *data, char *str);
char	*ft_strjoin(char *s1, char *s2, int dofree);
char	*ft_strdup(char *s);
char	*ft_cut_terminal(char *terminal, char *token);
char	*ft_add_space_before(char *str);
char	*ft_getenv(char **envp, int status, char *name, int *k);
char	*ft_strcpy(char *dest, char *src);
char	*ft_name(char *str);
char	*ft_itoa(int n);
char	*ft_tokennoquote(t_data *data, char *str);
char	*ft_cmdpath(char *cmd, char *env);
char	**ft_split(char *s, char c);
char	**ft_sortenv(char **envp, char **s, int size);
char	**ft_reallocargs(t_parse *current, char *token);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_cmdbuiltin(t_data *data, int outfd, char **cmd);
int		ft_cmdbuiltinlast(t_data *data, int outfd, char **cmd, char *terminal);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_check_quote(char *str);
int		ft_checkequal(char *env);
int		ft_parseredir(t_parse *current, char *token);
int		ft_checkname(char c, int pos);
int		ft_heredoc(char *terminal, char *limiter, char *next, t_data *data);

#endif
