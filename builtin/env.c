#include "../minishell.h"

void	ft_env(t_data *data, int outfd, char **cmd)
{
	int	i;

	if (cmd[1])
	{
		data->status = 1;
		ft_putstr_fd("minishell: env does not take any argument.\n", 1);
		return ;
	}
	i = 0;
	while (data->envp[i])
	{
		if (ft_checkenvname(data->envp[i]) == 1)
		{
			ft_putstr_fd(data->envp[i], outfd);
			ft_putstr_fd("\n", outfd);
		}
		i++;
	}
	data->status = 0;
}
