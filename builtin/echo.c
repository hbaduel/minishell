#include "../minishell.h"

void	ft_echo(char **cmd)
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
		ft_putstr_fd(cmd[start], 1);
		start++;
	}
	if (donl == 1)
		ft_putstr_fd("\n", 1);
	exit(0);
}
