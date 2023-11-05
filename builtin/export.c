#include "../minishell.h"

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

int	ft_checkisoption(t_data *data, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			ft_putstr_fd("minishell: export does not take any options.\n", 1);
			data->status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(t_data *data, char **cmd, int outfd)
{
	int	i;
	int	j;

	i = 1;
	if (!cmd[i])
	{
		ft_printexport(data->envp, outfd);
		data->status = 0;
		return ;
	}
	if (ft_checkisoption(data, cmd) == 1)
		return ;
	// while (cmd[i])
	// {
	// 	j = 0;
	// 	while (data->envp[j])
	// 	{
	// 		if ()
	// 	}
	// }
}
