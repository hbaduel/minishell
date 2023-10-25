#include "minishell.h"

int	ft_openfile(char *file, t_data *data, int which)
{
	int	fd;

	if (which == 0)
		fd = open(file, O_RDONLY, 0777);
	if (which == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (which == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (data->infilefd != 0 && which == 0)
		close(data->infilefd);
	if (data->outfilefd != 1 && which > 0)
		close(data->outfilefd);
	if (which == 0)
		data->infilefd = fd;
	if (which > 0)
		data->outfilefd = fd;
	return (0);
}
