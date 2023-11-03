#include "../minishell.h"

void	ft_echo(t_data *data, char **cmd, int outfd)
{
	int	donl;
	int	start;

	donl = 1;
	start = 1;
	if (ft_strcmp(cmd[1], "-n") == 0)
	{
		donl = 0;
		start = 2;
	}
	while (cmd[start])
	{
		ft_putstr_fd(cmd[start], outfd);
		if (cmd[start + 1])
			ft_putstr_fd(" ", outfd);
		start++;
	}
	if (donl == 1)
		ft_putstr_fd("\n", outfd);
	data->status = 0;
}
