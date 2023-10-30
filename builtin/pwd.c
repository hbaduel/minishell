#include "../minishell.h"

void	ft_pwd(int outfd, char **cmd)
{
	char	buff[1000];

	if (cmd[1])
		ft_exiterror("minishell: pwd does not take any argument.\n");
	getcwd(buff, 1000);
	ft_putstr_fd(buff, outfd);
	ft_putstr_fd("\n", outfd);
}
