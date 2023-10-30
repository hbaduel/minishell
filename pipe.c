#include "minishell.h"

int	ft_cmdbuiltin(t_data *data, int outfd, char **cmd, char **envp)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		ft_echo(cmd, outfd);
		return (1);
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_pwd(data, outfd, cmd);
		return (1);
	}
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_env(data, outfd, cmd, envp);
		return (1);
	}
	return (0);
}

void	ft_execcmd(char **cmd, char **envp, int outfd)
{
	char	*path;

	path = ft_cmdpath(cmd[0], envp);
	if (!path)
	{
		free(path);
		if (outfd != 1)
			dup2(1, outfd);
		path = ft_strjoin("minishell: command not found: ", cmd[0], 0);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		free(path);
		exit(0);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		ft_exitperror("execve");
		exit (0);
	}
}

int	ft_nextcmd(t_data *data, int infd, char **cmd, char **envp)
{
	pid_t	pid;
	int		tubefd[2];

	pipe(tubefd);
	if (ft_cmdbuiltin(data, tubefd[1], cmd, envp) == 1)
	{
		close(tubefd[1]);
		return (tubefd[0]);
	}
	pid = fork();
	if (pid == 0)
	{
		close(tubefd[0]);
		dup2(infd, 0);
		dup2(tubefd[1], 1);
		ft_execcmd(cmd, envp, tubefd[1]);
	}
	data->status = waitpid(pid, 0, 0);
	close(tubefd[1]);
	return (tubefd[0]);
}

void	ft_pipe(t_data *data, t_parse *parsing, char **envp)
{
	pid_t	cpid;
	int		i;
	int		infd;

	i = 1;
	infd = data->infilefd;
	while (i < data->ncmd)
	{
		while(parsing->type != CMD)
			parsing = parsing->next;
		infd = ft_nextcmd(data, infd, parsing->args, envp);
		parsing = parsing->next;
		i++;
	}
	while(parsing->type != CMD)
		parsing = parsing->next;
	if (ft_cmdbuiltin(data, data->outfilefd, parsing->args, envp) == 1)
		return ;
	cpid = fork();
	if (cpid == 0)
	{
		dup2(infd, 0);
		if (data->outfilefd != 1)
			dup2(data->outfilefd, 1);
		ft_execcmd(parsing->args, envp, data->outfilefd);
	}
	data->status = waitpid(cpid, 0, 0);
}
