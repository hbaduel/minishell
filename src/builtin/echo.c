/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:03:30 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/22 20:48:58 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkoptionecho(char **cmd, int *start)
{
	int	donl;
	int	i;

	donl = 1;
	while (cmd[*start] && ft_strncmp(cmd[*start], "-n", 2) == 0)
	{
		i = 1;
		while (cmd[*start][i] == 'n')
			i++;
		if (!cmd[*start][i])
			donl = 0;
		else
			return (donl);
		*start += 1;
	}
	return (donl);
}

void	ft_echo(t_data *data, char **cmd, int outfd)
{
	int	donl;
	int	start;

	start = 1;
	donl = ft_checkoptionecho(cmd, &start);
	while (cmd[start])
	{
		ft_putstr_fd(cmd[start], outfd);
		if (cmd[start + 1])
			ft_putstr_fd(" ", outfd);
		start++;
	}
	if (donl == 1)
		ft_putstr_fd("\n", outfd);
	data->status = 0;
}
