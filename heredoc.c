#include "minishell.h"

extern char	*terminal;

void	ft_putheredoc(char *res, char *line, char *limiter, t_data *data)
{
	pid_t	cpid;
	int		pipefd[2];

	free(line);
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
}

int		ft_checklimiter(char *limiter, char *next, char **res, t_data *data)
{
	char	*temp;
	int		i;
	int		j;

	*res = NULL;
	if (!next)
		return (0);
	i = 0;
	while (next[i])
	{
		j = i;
		while (next[j] != '\n' && next[j])
			j++;
		temp = malloc(sizeof(char) * (j - i + 1));
		j = 0;
		while (next[i] != '\n' && next[i])
		{
			temp[j] = next[i];
			j++;
			i++;
		}
		temp[j] = '\0';
		i++;
		if (ft_strcmp(limiter, temp) == 0)
		{
			ft_putheredoc(*res, temp, limiter, data);
			return (1);
		}
		*res = ft_strjoin(*res, temp, 1);
		*res = ft_strjoin(*res, temp, 1);
		free(temp);
	}
	return (0);
}

void	ft_heredoc(char *limiter, char *next, t_data *data)
{
	char	*heredoc;
	char	*res;

	printf("POUR VOIR LE PB A GERER DE HIER GO ft_heredoc (heredoc.c)\n"); // pb de parsing quand une seule ligne avec le \n
	if (ft_checklimiter(limiter, next, &res, data) == 1)
		return ;
	while (1)
	{
		heredoc = readline("heredoc> ");
		terminal = ft_strjoin(terminal, "\n", 1);
		terminal = ft_strjoin(terminal, heredoc, 1);
		if (ft_strcmp(heredoc, limiter) == 0)
		{
			ft_putheredoc(res, heredoc, limiter, data);
			return ;
		}
		res = ft_strjoin(res, heredoc, 1);
		res = ft_strjoin(res, "\n", 1);
		free(heredoc);
	}
}
