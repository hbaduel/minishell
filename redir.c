#include "minishell.h"

void	ft_openfile(char *file, t_data *data, int which)
{
	if (which == 0)
		data->infilefd = open(file, O_RDONLY, 0777);
	if (which == 1)
		data->outfilefd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (which == 2)
		data->outfilefd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (data->outfilefd < 0)
		ft_exiterror("open");
}
