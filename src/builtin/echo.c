/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:03:30 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 18:20:59 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_data *data, char **cmd, int outfd)
{
	int	donl;
	int	start;

	donl = 1;
	start = 1;
	if (ft_strcmp(cmd[1], "-n") == 0)
	{
		donl = 0;
		start = 2;
	}
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
