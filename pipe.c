#include "minishell.h"

void	ft_execcmd(t_data *data, char **cmd, char **envp)
{
	char	*path;

	path = ft_cmdpath(cmd[0], envp);
	if (!path[0])
	{
		free(path);
		if (data->outfilefd == 1)
		{
			path = ft_strjoin("minishell: command not found: ", cmd[0], 0);
			ft_putstr_fd(path, 1);
			ft_putstr_fd("\n", 1);
			free(path);
		}
		exit(0);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		ft_exiterror("execve");
		exit (0);
	}
}

void	ft_nextcmd(t_data *data, char **cmd, char **envp)
{
	pid_t	pid;
	int		tubefd[2];

	if (pipe(tubefd) == -1)
		ft_exiterror("pipe");
	pid = fork();
	if (pid == -1)
		ft_exiterror("fork");
	if (pid == 0)
	{
		close(tubefd[0]);
		dup2(tubefd[1], 1);
		ft_execcmd(data, cmd, envp);
	}
	waitpid(pid, NULL, 0);
	close(tubefd[1]);
	dup2(tubefd[0], 0);
}

void	ft_pipe(t_data *data, char **envp)
{
	pid_t	pid;
	int		i;
	char	**cmd;

	i = 0;
	while (i < data->ncmd)
	{
		ft_nextcmd(data, cmd, envp);
		i++;
	}
	pid = fork();
	if (pid == -1)
		ft_exiterror("fork");
	if (pid == 0)
	{
		dup2(data->outfilefd, 1);
		ft_execcmd(data, cmd, envp);
	}
	waitpid(pid, NULL, 0);
}
