/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:01:39 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 18:21:51 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	str = malloc (sizeof(char) * (ft_strlen(s) + 1));
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_parse	*ft_realloc(t_parse *current, t_parse *previous, char *token, int type)
{
	int		current_size;
	int		i;
	char	**new_args;

	current_size = 0;
	i = 0;
	while (previous->args[current_size])
		current_size++;
	new_args = malloc(sizeof(char *) * (current_size + 2));
	while (previous->args[i])
	{
		new_args[i] = previous->args[i];
		i++;
	}
	new_args[i] = ft_strdup(token);
	new_args[i + 1] = NULL;
	free(previous->args);
	previous->args = new_args;
	free(current);
	previous->type = type;
	return (previous);
}

void	ft_strncpy(char *dest, char *src, int n)
{
	if (n <= 0 || *src == '\0')
		*dest = '\0';
	else
	{
		*dest = *src;
		ft_strncpy(dest + 1, src + 1, n - 1);
	}
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_reallocargs(t_parse *current, char *token)
{
	int		current_size;
	int		i;
	char	**new_args;

	current_size = 0;
	i = 0;
	while (current->args[current_size])
		current_size++;
	new_args = malloc(sizeof(char *) * (current_size + 2));
	while (current->args[i])
	{
		new_args[i] = current->args[i];
		i++;
	}
	new_args[i] = ft_strdup(token);
	new_args[i + 1] = NULL;
	free(current->args);
	return (new_args);
}
