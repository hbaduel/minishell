#include "../minishell.h"

void	ft_echo(t_parse	*parse, int outfd)
{
	int	donl;
	int	start;

	donl = 1;
	start = 1;
	if (ft_strcmp(parse->args[1], "-n") == 0)
	{
		donl = 0;
		start = 2;
	}
	while (parse->args[start])
	{
		ft_putstr_fd(parse->args[start], outfd);
		start++;
	}
	if (donl == 1)
		ft_putstr_fd("\n", outfd);
	exit(0);
}
