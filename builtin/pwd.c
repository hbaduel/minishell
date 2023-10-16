#include "../minishell.h"

void	ft_pwd(char **cmd)
{
	char	buff[1000];
	getcwd(buff, 1000);
	ft_putstr_fd(buff, 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}
