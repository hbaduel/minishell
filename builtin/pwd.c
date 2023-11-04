#include "../minishell.h"

void	ft_pwd(t_data *data, int outfd, char **cmd)
{
	char	buff[1000];

	if (cmd[1])
	{
		data->status = 1;
		ft_putstr_fd("minishell: pwd does not take any argument.\n", 1);
		return ;
	}
	getcwd(buff, 1000);
	ft_putstr_fd(buff, outfd);
	ft_putstr_fd("\n", outfd);
	data->status = 0;
}
