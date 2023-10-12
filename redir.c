#include "minishell.h"

void	redir_input(char *file, t_data *data)
{
	char	*test;

	data->infilefd = open(file, O_RDONLY, 0777);
	if (data->infilefd < 0)
		ft_exiterror("open");
	dup2(data->infilefd, 0);
	test = ft_readfd(0);
	ft_putstr_fd(test, 1);
}

void	redir_output(char *file, t_data *data)
{

}

void	redir_append(char *file, t_data *data)
{

}
