/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:17:00 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/15 22:44:12 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_sizeheredoc(t_data *data, char	*str)
{
	char	*env;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\0'\
		&& str[i + 1] != '$'))
		{
			env = ft_getenv(data->envp, data->status, \
			ft_name(&str[i + 1]), &i);
			size += ft_strlen(env);
			free(env);
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size + 1);
}

char	*ft_dupheredoc(t_data *data, char *str)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * ft_sizeheredoc(data, str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\0'\
		&& str[i + 1] != '$'))
			ft_putenv(res, ft_getenv(data->envp, data->status, \
		ft_name(&str[i + 1]), &i), &j);
		else
		{
			res[j] = str[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	free(str);
	return (res);
}

void	ft_putheredoc(char *terminal, char *res, char *limiter, t_data *data)
{
	pid_t	cpid;
	int		pipefd[2];

	if (data->ncmd > 0)
	{
		pipe(pipefd);
		cpid = fork();
		if (cpid == 0)
		{
			close(pipefd[0]);
			res = ft_dupheredoc(data, res);
			ft_putstr_fd(res, pipefd[1]);
			ft_free_all(data, pipefd[1], terminal);
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

int	ft_heredoc(char *terminal, char *limiter, char *next, t_data *data)
{
	char	*heredoc;
	char	*res;

	res = NULL;
	while (1)
	{
		heredoc = readline("heredoc> ");
		if (!heredoc)
		{
			if (res)
				free(res);
			return (1);
		}
		if (ft_strcmp(heredoc, limiter) == 0)
		{
			free(heredoc);
			ft_putheredoc(terminal, res, limiter, data);
			return (0);
		}
		res = ft_strjoin(res, heredoc, 1);
		res = ft_strjoin(res, "\n", 1);
		free(heredoc);
	}
}
