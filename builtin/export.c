#include "../minishell.h"

int	ft_isalreadysort(char *env, char **sort)
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

char	**ft_sortenv(char **envp, char **sort, int size)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	sort[i] = NULL;
	while (i < size)
	{
		k = 0;
		while (ft_isalreadysort(envp[k], sort) == 1)
			k++;
		temp = envp[k];
		j = k + 1;
		while (envp[j])
		{
			if (ft_strcmp(temp, envp[j]) > 0 && ft_isalreadysort(envp[j], sort) == 0)
				temp = envp[j];
			j++;
		}
		sort[i] = temp;
		sort[i + 1] = NULL;
		i++;
	}
	return (sort);
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
		while(sort[i][j] != '=' && sort[i][j])
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
	}// demander s'il faut enlever le dernier env
	free(sort);
	*status = 0;
}

int	ft_addenvp(t_data *data, char *name, char *cmd)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(name, data->envp[i], ft_strlen(name)) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(cmd);
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

	i = 0;
	if (!cmd[1])
	{
		while (data->envp[i])
			i++;
		return (ft_printexport(&data->status, ft_sortenv(data->envp, malloc(sizeof(char *) * (i + 1)), i), outfd));
	}
	else if (cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell: export does not take any option.\n", 1);
		data->status = 1;
		return ;
	}
	while (cmd[i])
	{
		name = ft_getenvname(cmd[i]);
		//if (ft_checkarg())		faut check si le nom est ok (ponctuation, -, $, |, {}, [], @, +, /, \, #, vide, space/tab) et si y a quelque chose avant le =, s'il ya des nombres avant une lettre pas ok mais apres oui // dans parsing supprimer error accolade
			//ft_addenvp()
		i++;
	}
}
