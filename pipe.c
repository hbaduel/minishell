#include "minishell.h"

int	ft_cmdbuiltin(int outfd, char **cmd, char **envp)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		ft_echo(cmd, outfd);
		return (1);
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_pwd(outfd, cmd);
		return (1);
	}
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_env(outfd, cmd, envp);
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

int	ft_nextcmd(int infd, char **cmd, char **envp)
{
	pid_t	pid;
	int		tubefd[2];
	int		didbuiltin;

	pipe(tubefd);
	didbuiltin = ft_cmdbuiltin(tubefd[1], cmd, envp);
	if (didbuiltin == 1)
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
	waitpid(pid, 0, 0);
	close(tubefd[1]);
	return (tubefd[0]);
}

void	ft_pipe(t_data *data, t_parse *parsing, char **envp)
{
	pid_t	cpid;
	int		i;
	int		infd;
	int		didbuiltin;

	i = 1;
	infd = data->infilefd;
	while (i < data->ncmd)
	{
		while(parsing->type != CMD)
			parsing = parsing->next;
		infd = ft_nextcmd(infd, parsing->args, envp);
		parsing = parsing->next;
		i++;
	}
	while(parsing->type != CMD)
		parsing = parsing->next;
	didbuiltin = ft_cmdbuiltin(data->outfilefd, parsing->args, envp);
	cpid = fork();
	if (cpid == 0)
	{
		dup2(infd, 0);
		if (data->outfilefd != 1)
			dup2(data->outfilefd, 1);
		ft_execcmd(parsing->args, envp, data->outfilefd);
	}
	waitpid(cpid, 0, 0);
}
