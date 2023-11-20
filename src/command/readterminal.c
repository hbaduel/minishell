/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readterminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:18:24 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/20 15:15:07 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_openfile(char *file, t_data *data, int which)
{
	int	fd;

	if (which == 0)
		fd = open(file, O_RDONLY, 0777);
	if (which == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (which == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (data->infilefd != 0 && which == 0)
		close(data->infilefd);
	if (data->outfilefd != 1 && which > 0)
		close(data->outfilefd);
	if (which == 0)
		data->infilefd = fd;
	if (which > 0)
		data->outfilefd = fd;
	return (0);
}

void	ft_chooseaction(t_data *data, char *terminal)
{
	pid_t	cpid;
	int		didbuiltin;

	if (data->ncmd == 1)
	{
		while (data->parse->type != CMD)
			data->parse = data->parse->next;
		if (ft_cmdbuiltinlast(data, data->outfilefd, \
		data->parse->args, terminal) == 1)
			return ;
		cpid = fork();
		if (cpid == 0)
		{
			if (data->infilefd != 0)
				dup2(data->infilefd, 0);
			ft_execcmd(terminal, data->parse->args, data, data->outfilefd);
		}
		waitpid(cpid, &data->status, 0);
		data->status /= 256;
	}
	else if (data->ncmd > 1)
		ft_pipe(data, data->parse, terminal);
}

int	ft_rediropen(char *terminal, t_data *data)
{
	t_parse	*redir;
	int		operror;

	operror = 0;
	redir = data->parse;
	while (redir)
	{
		if (redir->type == OUTCOMPLET)
			operror = ft_openfile(redir->args[1], data, 1);
		if (redir->type == APPENDCOMP)
			operror = ft_openfile(redir->args[1], data, 2);
		if (redir->type == HDCOMPLET)
			operror = \
			ft_heredoc(terminal, redir->args[1], redir->args[2], data);
		if (redir->type == INCOMPLET)
			operror = ft_openfile(redir->args[1], data, 0);
		redir = redir->next;
		if (operror == 1)
			return (1);
	}
	return (0);
}

void	ft_readterminal(t_data *data)
{
	char	*terminal;

	while (1)
	{
		terminal = readline(data->display);
		if (!terminal)
		{
			ft_free_data(data);
			rl_clear_history();
			exit(0);
		}
		if (terminal[0])
		{
			data->parse = ft_parse(terminal, data);
			if (data->parse)
			{
				if (ft_rediropen(terminal, data) == 0 && data->ncmd > 0)
					ft_chooseaction(data, terminal);
				ft_freeline(data);
			}
			add_history(terminal);
		}
		free(terminal);
	}
}
