/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:34:44 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 19:36:29 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkredirin(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (!str[i + 1] || str[i + 1] == '>' || str[i + 1] == '|')
			{
				ft_putstr_fd("minishell: parse error near `<'\n", 1);
				return (1);
			}
			else if (str[i + 1] == '<' && \
			(!str[i + 2] || str[i + 2] == '<' || str[i + 2] == '|'))
			{
				ft_putstr_fd("minishell: parse error near `<<'\n", 1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_checkredirout(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			if (!str[i + 1] || str[i + 1] == '<' || str[i + 1] == '|')
			{
				ft_putstr_fd("minishell: parse error near `>'\n", 1);
				return (1);
			}
			else if (str[i + 1] == '>' && \
			(!str[i + 2] || str[i + 2] == '>' || str[i + 2] == '|'))
			{
				ft_putstr_fd("minishell: parse error near `>>'\n", 1);
				return (1);
			}
		}
		i++;
	}
	return (ft_checkredirin(str));
}

int	ft_quote(char *str, int *i, char quote)
{
	*i += 1;
	while (str[*i] != quote && str[*i])
		*i += 1;
	if (!str[*i])
	{
		ft_putstr_fd("Error : quotes have to be closed.\n", 1);
		return (1);
	}
	return (0);
}

int	ft_check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			if (ft_quote(str, &i, str[i]) == 1)
				return (1);
		}
		else if (str[i] == '\\' || str[i] == ';')
		{
			ft_putstr_fd("Error : '\\' and ';' are not interpreted.\n", 1);
			return (1);
		}
		i++;
	}
	return (ft_checkredirout(str));
}
