#include "minishell.h"

extern char	*terminal;

int	ft_cmdbuiltin(t_data *data, int outfd, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		ft_echo(data, cmd, outfd);
		return (1);
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_pwd(data, outfd, cmd);
		return (1);
	}
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_env(data, outfd, cmd);
		return (1);
	}
	if (ft_strcmp(cmd[0], "unset") == 0)
	{
		ft_unset(data, cmd);
		return (1);
	}
	if (ft_strcmp(cmd[0], "export") == 0)
	{
		ft_export(data, cmd, outfd);
		return (1);
	}
	return (0);
}
void	ft_free_data(t_data *data)
{
	int		i;

	while (data)
	{
		i = 0;
		while (data->envp[i])
		{
			free(data->envp[i]);
			i++;
		}
		free(data->envp);
	}
}


void	ft_free_all(t_data *data, int outfd)
{
	ft_free_parse(data->parse);
	if (outfd != data->outfilefd && outfd != 1)
		close(outfd);
	if (data->infilefd != 0)
		close(data->infilefd);
    if (data->outfilefd != 1)
		close(data->outfilefd);
	ft_free_data(data);
	rl_clear_history();
	free(terminal);
}

void	ft_execcmd(char **cmd, t_data *data, int outfd)
{
	char	*path;

	path = ft_cmdpath(cmd[0], data->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 1);
		ft_putstr_fd(cmd[0], 1);
		ft_putstr_fd("\n", 1);
		ft_free_all(data, outfd);
		exit(127);
	}
	if (outfd != 1)
		dup2(outfd, 1);
	if (execve(path, cmd, data->envp) == -1)
	{
		free(path);
		ft_free_all(data, outfd);
		perror("execve");
		exit (1);
	}
}

int	ft_nextcmd(t_data *data, int infd, char **cmd)
{
	pid_t	pid;
	int		tubefd[2];

	pipe(tubefd);
	if (ft_cmdbuiltin(data, tubefd[1], cmd) == 1)
	{
		close(tubefd[1]);
		return (tubefd[0]);
	}
	pid = fork();
	if (pid == 0)
	{
		close(tubefd[0]);
		dup2(infd, 0);
		ft_execcmd(cmd, data, tubefd[1]);
	}
	waitpid(pid, &data->status, 0);
	data->status /= 256;
	close(tubefd[1]);
	return (tubefd[0]);
}

void	ft_pipe(t_data *data, t_parse *parsing)
{
	pid_t	cpid;
	int		i;
	int		infd;

	i = 0;
	infd = data->infilefd;
	while (++i < data->ncmd)
	{
		while(parsing->type != CMD)
			parsing = parsing->next;
		infd = ft_nextcmd(data, infd, parsing->args);
		parsing = parsing->next;
	}
	while(parsing->type != CMD)
		parsing = parsing->next;
	if (ft_cmdbuiltin(data, data->outfilefd, parsing->args) == 1)
		return ;
	cpid = fork();
	if (cpid == 0)
	{
		dup2(infd, 0);
		ft_execcmd(parsing->args, data, data->outfilefd);
	}
	waitpid(cpid, &data->status, 0);
	data->status /= 256;
}
