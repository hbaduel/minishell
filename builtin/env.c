#include "../minishell.h"

void	ft_env(int outfd, char **cmd, char **envp)
{
	int	i;

	if (cmd[1])
		ft_exiterror("minishell: env does not take any argument.\n");
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], outfd);
		ft_putstr_fd("\n", outfd);
		i++;
	}
}
