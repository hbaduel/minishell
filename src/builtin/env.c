/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:03:32 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 18:21:01 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkequal(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(t_data *data, int outfd, char **cmd)
{
	int	i;

	if (cmd[1])
	{
		data->status = 1;
		ft_putstr_fd("minishell: env does not take any argument.\n", 1);
		return ;
	}
	i = 0;
	while (data->envp[i])
	{
		if (ft_checkequal(data->envp[i]) == 1)
		{
			ft_putstr_fd(data->envp[i], outfd);
			ft_putstr_fd("\n", outfd);
		}
		i++;
	}
	data->status = 0;
}
