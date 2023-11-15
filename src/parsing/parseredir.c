/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:21:29 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 18:21:34 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_duparg(t_parse *current, int type, char *token)
{
	current->type = type;
	current->args = malloc(sizeof(char *) * 2);
	current->args[0] = ft_strdup(token);
	current->args[1] = NULL;
}

int	ft_parseredir(t_parse *current, char *token)
{
	if (ft_strcmp(token, "<") == 0)
	{
		ft_duparg(current, INFILE, token);
		return (1);
	}
	else if (ft_strcmp(token, ">") == 0)
	{
		ft_duparg(current, OUTFILE, token);
		return (1);
	}
	else if (ft_strcmp(token, "<<") == 0)
	{
		ft_duparg(current, HEREDOC, token);
		return (1);
	}
	else if (ft_strcmp(token, ">>") == 0)
	{
		ft_duparg(current, APPEND, token);
		return (1);
	}
	return (0);
}

t_parse	*ft_parseredircomp(t_data *data, t_parse *current, char *token)
{
	if (current->previous->type == INFILE)
	{
		current = ft_realloc(current, current->previous, token, INCOMPLET);
		return (current);
	}
	else if (current->previous->type == OUTFILE)
	{
		current = ft_realloc(current, current->previous, token, OUTCOMPLET);
		return (current);
	}
	else if (current->previous->type == HEREDOC)
	{
		current = ft_realloc(current, current->previous, token, HDCOMPLET);
		return (current);
	}
	else if (current->previous->type == APPEND)
	{
		current = ft_realloc(current, current->previous, token, APPENDCOMP);
		return (current);
	}
	current = ft_newcmd(data, current, token);
	return (current);
}
