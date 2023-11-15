/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:03:40 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/15 00:56:38 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_data *data, int outfd, char **cmd)
{
	char	buff[10000];

	if (cmd[1])
	{
		data->status = 1;
		ft_putstr_fd("minishell: pwd does not take any argument.\n", 1);
		return ;
	}
	getcwd(buff, 1000);
	ft_putstr_fd(buff, outfd);
	ft_putstr_fd("\n", outfd);
	data->status = 0;
}
