#include "../minishell.h"

int	ft_checkenvname(char *env)
{
	int	i;

	while (env[i])
	{
		if (env[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_data *data, int outfd, char **cmd, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (ft_checkenvname(cmd[i]) == 0)
		{
			if (outfd != 1)
				dup2(1, outfd);
			ft_putstr_fd("unset: ", 1);
			ft_putstr_fd(cmd[i], 1);
			ft_exiterror(": invalid parameter name.\n");
		}
		j = 0;
		while (envp[j])
		{
			if (ft_checkexist(cmd[i], envp[j]) ==)
			{

			}
			j++;
		}

	}
}
