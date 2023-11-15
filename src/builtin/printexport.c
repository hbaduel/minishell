/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:08:56 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 18:21:07 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checksort(char *env, char **sort)
{
	int	i;

	i = 0;
	while (sort[i])
	{
		if (ft_strcmp(env, sort[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**ft_sortenv(char **envp, char **s, int size)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	s[i] = NULL;
	while (i < size)
	{
		k = 0;
		while (ft_checksort(envp[k], s) == 1)
			k++;
		temp = envp[k];
		j = k + 1;
		while (envp[j])
		{
			if (ft_strcmp(temp, envp[j]) > 0 && ft_checksort(envp[j], s) == 0)
				temp = envp[j];
			j++;
		}
		s[i] = temp;
		s[i + 1] = NULL;
		i++;
	}
	return (s);
}

void	ft_printexport(int *status, char **sort, int outfd)
{
	int	i;
	int	j;

	i = 0;
	while (sort[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", outfd);
		while (sort[i][j] != '=' && sort[i][j])
		{
			write(outfd, &sort[i][j], 1);
			j++;
		}
		if (sort[i][j] == '=')
		{
			ft_putstr_fd("=\"", outfd);
			ft_putstr_fd(&sort[i][j + 1], outfd);
			write(outfd, "\"", 1);
		}
		write(outfd, "\n", 1);
		i++;
	}
	free(sort);
	*status = 0;
}
