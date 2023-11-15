/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choosebuiltin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:40:36 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/15 13:47:26 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmdbuiltintwo(t_data *data, int outfd, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		ft_echo(data, cmd, outfd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_pwd(data, outfd, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_env(data, outfd, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		ft_cd(data, cmd);
		return (1);
	}
	return (0);
}

int	ft_cmdbuiltinlast(t_data *data, int outfd, char **cmd, char *terminal)
{
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		ft_free_all(data, outfd, terminal);
		exit(0);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		ft_unset(data, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		ft_export(data, cmd, outfd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		ft_cd(data, cmd);
		return (1);
	}
	return (ft_cmdbuiltintwo(data, outfd, cmd));
}

int	ft_cmdbuiltin(t_data *data, int outfd, char **cmd)
{
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		ft_unset(data, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		ft_export(data, cmd, outfd);
		return (1);
	}
	return (ft_cmdbuiltintwo(data, outfd, cmd));
}
