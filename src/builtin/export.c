/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:03:35 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 18:21:03 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_reallocenvpmore(char **envp, char *new, int size)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		temp[i] = envp[i];
		i++;
	}
	temp[i] = ft_strdup(new);
	temp[i + 1] = NULL;
	free(envp);
	return (temp);
}

void	ft_addenvp(t_data *data, char *name, char *cmd)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(name, data->envp[i], ft_strlen(name)) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(cmd);
			return ;
		}
		i++;
	}
	data->envp = ft_reallocenvpmore(data->envp, cmd, i);
}

int	ft_checkarg(char *name, int i, int isletter)
{
	if (!name[i])
	{
		ft_putstr_fd("export: not valid in this context: ", 1);
		ft_putstr_fd(name, 1);
		write(1, "\n", 1);
		return (1);
	}
	while (name[i])
	{
		if (((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && \
		name[i] <= 'z')) && isletter == 0)
			isletter = 1;
		else if ((name[i] >= 32 && name[i] <= 47) || name[i] == '\t' || \
		((name[i] >= '0' || name[i] <= '9') && isletter == 0) || (name[i] >= 58 \
		&& name[i] <= 64) || (name[i] >= 91 && name[i] <= 96) || \
		(name[i] >= 123 && name[i] <= 126))
		{
			ft_putstr_fd("export: not valid in this context: ", 1);
			ft_putstr_fd(name, 1);
			write(1, "\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(t_data *data, char **cmd, int outfd)
{
	char	*name;
	int		i;

	i = 1;
	if (!cmd[1])
	{
		while (data->envp[i])
			i++;
		return (ft_printexport(&data->status, \
		ft_sortenv(data->envp, malloc(sizeof(char *) * (i + 1)), i), outfd));
	}
	else if (cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell: export does not take any option.\n", 1);
		data->status = 1;
		return ;
	}
	while (cmd[i++])
	{
		name = ft_name(cmd[i]);
		if (ft_checkarg(name, 0, 0) == 0)
			ft_addenvp(data, name, cmd[i]);
		free(name);
	}
	data->status = 0;
}
