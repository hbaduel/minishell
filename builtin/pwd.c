#include "../minishell.h"

void	ft_pwd(t_data *data, int outfd, char **cmd)
{
	char	buff[1000];

	if (cmd[1])
	{
		if (outfd != 1)
			dup2(1, outfd);
		ft_exiterror("minishell: pwd does not take any argument.\n");
	}
	getcwd(buff, 1000);
	ft_putstr_fd(buff, 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}
