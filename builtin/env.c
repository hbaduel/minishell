#include "../minishell.h"

void	ft_env(t_data *data, int outfd, char **cmd, char **envp)
{
	int	i;

	if (cmd[1])
	{
		data->status = 1;
		ft_putstr_fd("minishell: env does not take any argument.\n", 1);
		return ;
	}
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], outfd);
		ft_putstr_fd("\n", outfd);
		i++;
	}
}
