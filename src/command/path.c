/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:42:50 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/15 00:19:59 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_accessexecutable(char *cmd, char *env)
{
	free(env);
	if (access(cmd, R_OK) == 0)
		return (ft_strdup(cmd));
	else
	{
		ft_putstr_fd("minishell: no such file or directory: ", 1);
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd("\n", 1);
		return (NULL);
	}
}

int	ft_checkexecutable(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	ft_nopath(char *cmd, char *env, char **path, char *command)
{
	ft_freedoubletab(path);
	free(command);
	free(env);
	ft_putstr_fd("minishell: command not found: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd("\n", 1);
}

char	*ft_accesscmd(char *cmd, char *env)
{
	char	**path;
	char	*res;
	char	*command;
	int		i;

	command = ft_strjoin("/", cmd, 0);
	path = ft_split(env, ':');
	i = 0;
	while (path[i])
	{
		res = ft_strjoin(path[i], command, 0);
		if (access(res, R_OK) == 0)
		{
			ft_freedoubletab(path);
			free(env);
			free(command);
			return (res);
		}
		free(res);
		i++;
	}
	ft_nopath(cmd, env, path, command);
	return (NULL);
}

char	*ft_cmdpath(char *cmd, char *env)
{
	if (ft_checkexecutable(cmd) == 1)
		return (ft_accessexecutable(cmd, env));
	if (!env)
	{
		ft_putstr_fd("minishell: command not found: ", 1);
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd("\n", 1);
		return (NULL);
	}
	return (ft_accesscmd(cmd, env));
}
