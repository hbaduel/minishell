/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:19:38 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/21 14:51:01 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_cutquote(char *terminal, char delim)
{
	char	*new;
	int		start;
	int		end;
	int		i;

	start = 0;
	while (terminal[start] != delim && terminal[start])
		start++;
	end = start;
	while (terminal[end])
		end++;
	new = malloc(sizeof(char) * (end - start + 1));
	start++;
	i = 0;
	while (start < end)
	{
		new[i] = terminal[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_cutsize(char *term, int *i, int *j)
{
	char	delim;

	*i = 0;
	while (term[*i] != ' ' && term[*i] && term[*i] != '\t')
	{
		if (term[*i] == '\'' || term[*i] == '\"')
		{
			delim = term[*i];
			*i += 1;
			while (term[*i] != delim && term[*i])
				*i += 1;
		}
		*i += 1;
	}
	*j = *i;
	while (term[*j])
		*j += 1;
}

char	*ft_cutnoquote(char *terminal)
{
	char	*newterminal;
	int		start;
	int		end;
	int		i;

	ft_cutsize(terminal, &start, &end);
	newterminal = malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (start < end)
	{
		newterminal[i] = terminal[start];
		start++;
		i++;
	}
	newterminal[i] = '\0';
	return (newterminal);
}

char	*ft_cut_terminal(char *terminal, char *token)
{
	char	*newterminal;
	int		start;
	int		i;

	if (!token)
	{
		free(terminal);
		return (NULL);
	}
	start = 0;
	while ((terminal[start] == ' ' || terminal[start] == '\t') \
	&& terminal[start])
		start++;
	if (!terminal[start])
		newterminal = NULL;
	else if (terminal[start] == '\'' || terminal[start] == '\"')
		newterminal = ft_cutquote(&terminal[start + 1], terminal[start]);
	else
		newterminal = ft_cutnoquote(&terminal[start]);
	free(terminal);
	return (newterminal);
}
