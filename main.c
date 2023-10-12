#include "minishell.h"

char	*terminal;

char	*ft_cmdpath(char *cmd, char **envp)
{
	pid_t	cpid;
	char	*res;
	char	*path[2];
	int		tubefd[2];

	path[0] = "which";
	path[1] = cmd;
	path[2] = NULL;
	if (pipe(tubefd) == -1)
		ft_exiterror("pipe");
	cpid = fork();
	if (cpid == -1)
		ft_exiterror("fork");
	if (cpid == 0)
	{
		close(tubefd[0]);
		dup2(tubefd[1], 1);
		close(tubefd[1]);
		execve("/usr/bin/which", path, envp);
	}
	waitpid(cpid, NULL, 0);
	close(tubefd[1]);
	res = ft_readfd(tubefd[0]);
	close(tubefd[0]);
	return (res);
}

void	ft_chooseaction(t_data *data)
{
	int		i;

	i = 0;
	while (terminal[i])
	{
		if (terminal[i] == '<')
		{
			if (terminal[i + 1] == '<')
			{
				ft_heredoc("fin");
				i++;
			}
			else
				redir_input("test", data);
			i++;
		}
		/*if (terminal[i] == '>')
		{
			if (terminal[i + 1] == '>')
			{
				redir_append;
				i++;
			}
			else
				redir_outputput();
			i++;
		}*/
		i++;
	}
	if (data->infilefd != -1)
		close(data->infilefd);
}

void	ft_readterminal(t_data *data)
{
	while (1)
	{
		terminal = readline("\e[1;35mmi\e[1;34mni\e[1;32msh\e[1;33mel\e[1;31ml>\e[0;37m ");
		if (ft_strcmp(terminal, "exit") == 0)
		{
			free(terminal);
			return ;
		}
		ft_chooseaction(data);
		add_history(terminal);
		free(terminal);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->infilefd = -1;
	ft_readterminal(data);
	rl_clear_history();
	return (0);
}
