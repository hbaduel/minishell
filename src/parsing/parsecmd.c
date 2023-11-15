/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:59:02 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 18:21:30 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parse	*ft_parsecmdarg(t_data *data, t_parse *current, char *token)
{
	t_parse	*temp;

	if (current->previous->type == CMD)
	{
		current->previous->args = \
		ft_reallocargs(current->previous, token);
		current = current->previous;
		free(current->next);
		return (current);
	}
	else if ((current->previous->type >= 7 && \
	current->previous->type <= 10) && data->pipe_detector == 0)
	{
		temp = current;
		while (temp && temp->type != CMD)
			temp = temp->previous;
		temp->args = ft_reallocargs(temp, token);
		current = current->previous;
		free(current->next);
		return (current);
	}
}

t_parse	*ft_newcmd(t_data *data, t_parse *current, char *token)
{
	if (data->pipe_detector == 1)
	{
		current->type = CMD;
		current->args = malloc(sizeof(char *) * 2);
		current->args[0] = ft_strdup(token);
		current->args[1] = NULL;
		data->pipe_detector = 0;
		data->ncmd++;
		return (current);
	}
	current = ft_parsecmdarg(data, current, token);
	return (current);
}

t_parse	*ft_parsefirst(t_data *data, t_parse *current, char *token)
{
	if (!current->previous)
	{
		current->type = CMD;
		current->args = malloc(sizeof(char *) * 2);
		current->args[0] = ft_strdup(token);
		current->args[1] = NULL;
		data->ncmd++;
		data->pipe_detector = 0;
		return (current);
	}
	current = ft_parseredircomp(data, current, token);
	return (current);
}

t_parse	*ft_newpipe(t_data *data, t_parse *current, char *token, char *line)
{
	if (ft_strcmp(token, "|") == 0)
	{
		if (!current->previous || data->pipe_detector == 1)
		{
			free(token);
			free(line);
			current = current->previous;
			free(current->next);
			current->next = NULL;
			ft_free_parse(data->parse);
			ft_putstr_fd("Minishell : parse error near '|'\n", 1);
			return (NULL);
		}
		data->pipe_detector = 1;
		current = current->previous;
		free(current->next);
		return (current);
	}
	current = ft_parsefirst(data, current, token);
	return (current);
}
