#include "minishell.h"

void	redir_input(char *file, t_data *data)
{
	data->infilefd = open(file, O_RDONLY, 0777);
	if (data->infilefd < 0)
		ft_exiterror("open");
	dup2(data->infilefd, 0);
}

void	redir_output(char *file, t_data *data)
{
	data->outfilefd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->outfilefd < 0)
		ft_exiterror("open");
	dup2(data->outfilefd, 1);
}

void	redir_append(char *file, t_data *data)
{
	data->outfilefd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (data->outfilefd < 0)
		ft_exiterror("open");
	dup2(data->outfilefd, 1);
}
