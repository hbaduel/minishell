/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:57:40 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/15 00:11:30 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrlc(int i)
{
	(void) i;
	kill(0, 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		i;

	(void) argc;
	(void) argv;
	signal(SIGINT, &ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	data = malloc(sizeof(t_data));
	data->status = 0;
	data->ncmd = 0;
	data->infilefd = 0;
	data->outfilefd = 1;
	i = 0;
	while (envp[i])
		i++;
	data->envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp[i] = NULL;
	ft_readterminal(data);
}
