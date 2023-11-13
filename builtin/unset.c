#include "../minishell.h"

int	ft_checkexist(char *unset, char *env)
{
	int	i;

	i = 0;
	if (ft_checkequal(unset) == 1)
		return (0);
	while (unset[i] == env[i] && unset[i] && env[i])
		i++;
	if (!unset[i] && !env[i])
		return (1);
	if (!unset[i] && env[i] == '=')
		return (1);
	return (0);
}

char	**ft_reallocenvpless(char **envp, int donot)
{
	char **temp;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	temp = malloc(sizeof(char *) * i);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != donot)
		{
			temp[j] = envp[i];
			j++;
		}
		else
			free(envp[i]);
		i++;
	}
	temp[j] = NULL;
	free(envp);
	return (temp);
}

void	ft_unset(t_data *data, char **cmd)
{
	int		i;
	int		j;

	i = 1;
	if (cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell: bad option: unset does not take any option.\n", 1);
		data->status = 1;
		return ;
	}
	while (cmd[i])
	{
		j = 0;
		while (data->envp[j])
		{
			if (ft_checkexist(cmd[i], data->envp[j]) == 1)
			{
				data->envp = ft_reallocenvpless(data->envp, j);
				break ;
			}
			j++;
		}
		i++;
	}
	data->status = 0;
}
