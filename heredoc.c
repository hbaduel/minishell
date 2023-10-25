#include "minishell.h"

extern char	*terminal;

int		ft_checklimiter(char *limiter)
{
	int	i;
	int	j;

	i = 0;
	while (terminal[i] != '\n' && terminal[i])
		i++;
	while (terminal[i])
	{
		j = 0;
		while (terminal[i] == limiter[j])
		{
			if (limiter[j + 1] == '\0' && terminal[i + 1] == '\0')
				return (1);
			i++;
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_heredoc(char *limiter, t_data *data)
{
	char	*heredoc;
	char	*res;
	pid_t	cpid;
	int		pipefd[2];

	res = NULL;
	if (ft_checklimiter(limiter) == 1)
		return ; // a corriger dans le parse : si utilisation de l'historique que des \n donc considere que le limiter est tout ce qu'il y a apres
	while (1)
	{
		heredoc = readline("heredoc> ");
		terminal = ft_strjoin(terminal, "\n", 1);
		terminal = ft_strjoin(terminal, heredoc, 1);
		if (ft_strcmp(heredoc, limiter) == 0)
		{
			free(heredoc);
			if (data->ncmd > 0)
			{
				pipe(pipefd);
				cpid = fork();
				if (cpid == 0)
				{
					close(pipefd[0]);
					ft_putstr_fd(res, pipefd[1]);
					free(res);
					exit(0);
				}
				waitpid(cpid, 0, 0);
				close(pipefd[1]);
				if (data->infilefd != 0)
					close(data->infilefd);
				data->infilefd = pipefd[0];
			}
			free(res);
			return ;
		}
		res = ft_strjoin(res, heredoc, 1);
		res = ft_strjoin(res, "\n", 1);
		free(heredoc);
	}
}
