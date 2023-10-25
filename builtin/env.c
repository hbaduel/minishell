#include "../minishell.h"

void	ft_env(t_data *data, int outfd, char **cmd, char **envp)
{
	int	i;

	if (cmd[1])
	{
		if (outfd != 1)
			dup2(1, outfd);
		ft_exiterror("minishell: env does not take any argument.\n");
	}
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	exit(0);
}
