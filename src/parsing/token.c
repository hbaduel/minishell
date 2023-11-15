/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:19:52 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 18:21:39 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tokensize(t_data *data, char *str, char delim)
{
	char	*env;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (str[i] != delim && str[i])
	{
		if (delim == ' ' && str[i] == '\t')
			break ;
		if (str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\0'\
		&& str[i + 1] != '$') && delim != '\'')
		{
			env = ft_getenv(data->envp, data->status, ft_name(&str[i + 1]), &i);
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

char	*ft_tokenquote(t_data *data, char *str, char delim)
{
	char	*nexttoken;
	int		i;
	int		j;

	nexttoken = malloc(sizeof(char) * (ft_tokensize(data, str, delim)));
	i = 0;
	j = 0;
	while (str[i] != delim && str[i])
	{
		if (delim != '\'' && str[i] == '$' && (str[i + 1] != ' ' && \
		str[i + 1] != '\0' && str[i + 1] != '$'))
			ft_putenv(nexttoken, \
			ft_getenv(data->envp, data->status, ft_name(&str[i + 1]), &i), &j);
		else
		{
			nexttoken[j] = str[i];
			j++;
			i++;
		}
	}
	nexttoken[j] = '\0';
	return (nexttoken);
}

char	*ft_quotemidtoken(t_data *data, char *nexttoken, char *str, int j)
{
	char	*temp;
	char	delim;
	int		i;

	i = 1;
	delim = str[0];
	nexttoken[j] = '\0';
	temp = ft_tokenquote(data, &str[i], str[0]);
	nexttoken = ft_strjoin(nexttoken, temp, 1);
	free(temp);
	while (str[i] != delim)
		i++;
	if (str[i + 1] != ' ' && str[i + 1] != '\t' && str[i + 1])
	{
		temp = ft_tokennoquote(data, &str[i + 1]);
		nexttoken = ft_strjoin(nexttoken, temp, 1);
		free(temp);
	}
	return (nexttoken);
}

char	*ft_tokennoquote(t_data *data, char *str)
{
	char	*nexttoken;
	int		i;
	int		j;

	nexttoken = malloc(sizeof(char) * (ft_tokensize(data, str, ' ')));
	i = 0;
	j = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i])
	{
		if (str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\0'\
		&& str[i + 1] != '$'))
			ft_putenv(nexttoken, ft_getenv(data->envp, data->status, \
			ft_name(&str[i + 1]), &i), &j);
		else if (str[i] == '\'' || str[i] == '\"')
			return (ft_quotemidtoken(data, nexttoken, &str[i], j));
		else
		{
			nexttoken[j] = str[i];
			j++;
			i++;
		}
	}
	nexttoken[j] = '\0';
	return (nexttoken);
}

char	*ft_strtok(t_data *data, char *str)
{
	int	start;
	int	end;
	int	i;

	if (!str)
		return (NULL);
	start = 0;
	end = 0;
	i = 0;
	while ((str[start] == ' ' || str[start] == '\t') && str[start])
		start++;
	if (!str[start])
		return (NULL);
	if (str[start] == '\'' || str[start] == '"')
		return (ft_tokenquote(data, &str[start + 1], str[start]));
	else
		return (ft_tokennoquote(data, &str[start]));
}
