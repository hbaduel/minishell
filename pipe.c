#include "minishell.h"

void	ft_cmdbuiltin(t_data *data, int outfd, char **cmd, char **envp)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(data, outfd, cmd);
	if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(data, outfd, cmd, envp);
}

void	ft_execcmd(t_data *data, char **cmd, char **envp, int outfd)
{
	char	*path;

	ft_cmdbuiltin(data, outfd, cmd, envp);
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

void	ft_nextcmd(t_data *data, char **cmd, char **envp)
{
	pid_t	pid;
	int		tubefd[2];

	if (pipe(tubefd) == -1)
		ft_exitperror("pipe");
	pid = fork();
	if (pid == -1)
		ft_exitperror("fork");
	if (pid == 0)
	{
		close(tubefd[0]);
		dup2(tubefd[1], 1);
		ft_execcmd(data, cmd, envp, tubefd[1]);
	}
	waitpid(pid, NULL, 0);
	dup2(tubefd[0], 0);
	close(tubefd[1]);
}

void	ft_pipe(t_data *data, t_parse *parsing, char **envp)
{
	pid_t	pid;
	int		i;

	i = 1;
	while (i < data->ncmd)
	{
		while(parsing->type != CMD)
			parsing = parsing->next;
		ft_nextcmd(data, parsing->args, envp);
		parsing = parsing->next;
		i++;
	}
	if (data->outfilefd != 1)
		dup2(data->outfilefd, 1);
	while(parsing->type != CMD)
		parsing = parsing->next;
	ft_execcmd(data, parsing->args, envp, data->outfilefd);
}
