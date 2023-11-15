/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:03:26 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/15 15:06:59 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_envpchange(t_data *data, char *env)
{
	char	*oldpwd;
	char	*temp;

	oldpwd = ft_getenv(data->envp, 0, ft_name("PWD"), NULL);
	if (oldpwd)
	{
		temp = ft_strjoin("OLDPWD=", oldpwd, 0);
		free(oldpwd);
		ft_addenvp(data, "OLDPWD", temp);
		free(temp);
	}
	temp = ft_strjoin("PWD=", env, 0);
	ft_addenvp(data, "PWD", temp);
	free(temp);
}

void	ft_openhome(t_data *data)
{
	char	*env;

	env = ft_getenv(data->envp, 0, ft_name("HOME"), NULL);
	if (!env)
	{
		data->status = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		return ;
	}
	if (chdir((const char *)env) == -1)
	{
		data->status = 1;
		perror("chdir");
		return ;
	}
	ft_envpchange(data, env);
	free(env);
	data->status = 0;
}

void	ft_openarg(t_data *data, char *arg)
{
	if (ft_strcmp("~", arg) == 0)
	{
		ft_openhome(data);
		return ;
	}
	if (chdir((const char *)arg) == -1)
	{
		data->status = 1;
		perror("chdir");
		return ;
	}
	ft_envpchange(data, arg);
	data->status = 0;
}

void	ft_cd(t_data *data, char **cmd)
{
	if (!cmd[1])
	{
		ft_openhome(data);
		return ;
	}
	if (cmd[2])
	{
		data->status = 1;
		ft_putstr_fd("minishell: cd: too many arguments\n", 1);
		return ;
	}
	ft_openarg(data, cmd[1]);
}
