/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:19:41 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/21 15:19:07 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_envvalue(char *env, int start)
{
	char	*res;
	int		end;
	int		i;

	end = start;
	while (env[end])
		end++;
	res = malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (env[start])
	{
		res[i] = env[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_checkname(char c, int pos)
{
	if (!c || c == '\'' || c == '\"' || c == ' ' || c == '=' \
	|| c == '\t' || c == '@' || c == '!' || c == '(' || c == ')' \
	|| c == '{' || c == '}' || c == '[' || c == ']' || c == '<' \
	|| c == '>' || c == '+' || c == '-' || c == ':' || c == ';' \
	|| c == ',' || c == '.' || c == '*' || c == '^' || c == '%' \
	|| c == '~' || c == '/')
		return (1);
	else if (c == '?' && pos != 0)
		return (1);
	else
		return (0);
}

char	*ft_name(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (ft_checkname(str[i], i) == 0)
		i++;
	res = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (ft_checkname(str[i], i) == 0)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_getenv(char **envp, int status, char *name, int *k)
{
	int		i;
	int		j;

	i = 0;
	if (k)
		*k += ft_strlen(name) + 1;
	if (ft_strcmp(name, "?") == 0)
	{
		free(name);
		return (ft_itoa(status));
	}
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == name[j] && name[j] && envp[i][j])
			j++;
		if (envp[i][j] == '=' && envp[i][j + 1] && name[j] == '\0')
		{
			free(name);
			return (ft_envvalue(envp[i], j + 1));
		}
		i++;
	}
	free(name);
	return (NULL);
}

void	ft_putenv(char *nexttoken, char *env, int *j)
{
	int		k;

	k = 0;
	if (!env)
		return ;
	while (env[k])
	{
		nexttoken[*j] = env[k];
		k++;
		*j += 1;
	}
	free(env);
}
