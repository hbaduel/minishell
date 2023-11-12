#include "../minishell.h"

int	ft_checkexist(char *unset, char *env)
{
	int	i;

	i = 0;
	while (unset[i] == env[i] && unset[i] && env[i])
		i++;
	if (!unset[i] && !env[i])
		return (1);
	if (!unset[i] && env[i] == '=')
		return (1);
	return (0);
}

int	ft_checkexistvalue(char *env)
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
	char	*temp;
	int		i;
	int		j;
	int		size;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (data->envp[j])
		{
			if (ft_checkvalue(cmd[i]) == 1)
				break ;
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
