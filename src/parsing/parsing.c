/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:19:44 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/24 21:24:31 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parse	*ft_checkredir(t_parse *first, t_parse *temp)
{
	while (temp)
	{
		if (temp->type == INFILE)
		{
			ft_putstr_fd("minishell : parse error near `<'\n", 1);
			return (ft_free_parse(first));
		}
		else if (temp->type == OUTFILE)
		{
			ft_putstr_fd("minishell : parse error near `>'\n", 1);
			return (ft_free_parse(first));
		}
		else if (temp->type == HEREDOC)
		{
			ft_putstr_fd("minishell : parse error near `<<'\n", 1);
			return (ft_free_parse(first));
		}
		else if (temp->type == APPEND)
		{
			ft_putstr_fd("minishell : parse error near `>>'\n", 1);
			return (ft_free_parse(first));
		}
		temp = temp->next;
	}
	return (first);
}

t_parse	*ft_setup(t_data *data, char *terminal, char **line)
{
	int	i;
	int	ok;

	i = 0;
	ok = 0;
	while (terminal[i])
	{
		if (terminal[i] != ' ' && terminal[i] != '\t')
			ok = 1;
		i++;
	}
	if (ok == 0)
		return (NULL);
	if (ft_check_quote(terminal) == 1)
		return (NULL);
	*line = ft_add_space_before(ft_strdup(terminal));
	data->parse = malloc(sizeof(t_parse));
	data->pipe_detector = 1;
	data->parse->previous = NULL;
	return (data->parse);
}

t_parse	*ft_setupwhile(t_parse *current, char *token)
{
	current->next = malloc(sizeof(t_parse));
	current->next->previous = current;
	current = current->next;
	free(token);
	return (current);
}

t_parse	*ft_parse(char *terminal, t_data *data)
{
	t_parse	*current;
	char	*token;
	char	*line;

	current = ft_setup(data, terminal, &line);
	if (!current)
		return (NULL);
	token = ft_strtok(data, line);
	line = ft_cut_terminal(line, token);
	while (token != NULL)
	{
		if (ft_parseredir(current, token) == 0)
		{
			current = ft_newpipe(data, current, token, line);
			if (!current)
				return (NULL);
		}
		current = ft_setupwhile(current, token);
		token = ft_strtok(data, line);
		line = ft_cut_terminal(line, token);
	}
	current->previous->next = NULL;
	free(current);
	return (ft_checkredir(data->parse, data->parse));
}
