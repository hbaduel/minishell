#include "../minishell.h"

void	ft_pwd(int outfd)
{
	char	buff[1000];
	getcwd(buff, 1000);
	ft_putstr_fd(buff, outfd);
	ft_putstr_fd("\n", outfd);
	exit(0);
}
