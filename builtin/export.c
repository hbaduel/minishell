#include "minishell.h"

void	ft_printexport(char **envp, int outfd)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", outfd);
		while(envp[i][j] != '=' && envp[i][j])
		{
			write(outfd, &envp[i][j], 1);
			j++;
		}
		if (envp[i][j] == '=')
		{
			write(outfd, "=", 1);
			write(outfd, "\"", 1);
			ft_putstr_fd(&envp[i][j +1], outfd);
			write(outfd, "\"", 1);
		}
		write(outfd, "\n", 1);
		i++;
	}
}

void	ft_export(t_data *data, char **cmd, int outfd)
{
	int	i;

	i = 1;
	if (!cmd[i])
	{
		ft_printexport(data->envp, outfd);
		return ;
	}
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			ft_putstr_fd("minishell: export does not take any options.\n", 1);
			return ;
		}

	}
}
