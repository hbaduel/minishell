/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:14:56 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 20:20:56 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execcmd(char *term, char **cmd, t_data *data, int outfd)
{
	char	*path;

	path = ft_cmdpath(cmd[0], ft_getenv(data->envp, 0, ft_name("PATH"), NULL));
	if (!path)
	{
		ft_free_all(data, outfd, term);
		exit(127);
	}
	if (outfd != 1)
		dup2(outfd, 1);
	if (execve(path, cmd, data->envp) == -1)
	{
		free(path);
		ft_free_all(data, outfd, term);
		perror("execve");
		exit (1);
	}
}

int	ft_nextcmd(t_data *data, int infd, char **cmd, char *term)
{
	pid_t	pid;
	int		tubefd[2];

	pipe(tubefd);
	if (ft_cmdbuiltin(data, tubefd[1], cmd) == 1)
	{
		close(tubefd[1]);
		return (tubefd[0]);
	}
	pid = fork();
	if (pid == 0)
	{
		close(tubefd[0]);
		dup2(infd, 0);
		ft_execcmd(term, cmd, data, tubefd[1]);
	}
	waitpid(pid, &data->status, 0);
	data->status /= 256;
	close(tubefd[1]);
	return (tubefd[0]);
}

void	ft_pipe(t_data *data, t_parse *parsing, char *terminal)
{
	pid_t	cpid;
	int		i;
	int		infd;

	i = 0;
	infd = data->infilefd;
	while (++i < data->ncmd)
	{
		while (parsing->type != CMD)
			parsing = parsing->next;
		infd = ft_nextcmd(data, infd, parsing->args, terminal);
		parsing = parsing->next;
	}
	while (parsing->type != CMD)
		parsing = parsing->next;
	if (ft_cmdbuiltinlast(data, data->outfilefd, parsing->args, terminal) == 1)
		return ;
	cpid = fork();
	if (cpid == 0)
	{
		dup2(infd, 0);
		ft_execcmd(terminal, parsing->args, data, data->outfilefd);
	}
	waitpid(cpid, &data->status, 0);
	data->status /= 256;
}
