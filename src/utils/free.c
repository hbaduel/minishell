/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:00:28 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 18:21:42 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freedoubletab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_parse	*ft_free_parse(t_parse *parse)
{
	t_parse	*temp;
	int		i;

	while (parse)
	{
		i = 0;
		while (parse->args[i])
		{
			free(parse->args[i]);
			i++;
		}
		free(parse->args);
		temp = parse;
		parse = parse->next;
		free(temp);
	}
	return (NULL);
}

void	ft_free_data(t_data *data)
{
	int		i;

	i = 0;
	while (data->envp[i])
	{
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
	free(data);
}

void	ft_freeline(t_data *data)
{
	ft_free_parse(data->parse);
	if (data->infilefd != 0)
		close(data->infilefd);
	if (data->outfilefd != 1)
		close(data->outfilefd);
	data->ncmd = 0;
	data->infilefd = 0;
	data->outfilefd = 1;
}

void	ft_free_all(t_data *data, int outfd, char *terminal)
{
	ft_free_parse(data->parse);
	if (outfd != data->outfilefd && outfd != 1)
		close(outfd);
	if (data->infilefd != 0)
		close(data->infilefd);
	if (data->outfilefd != 1)
		close(data->outfilefd);
	ft_free_data(data);
	rl_clear_history();
	free(terminal);
}
