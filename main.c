#include "minishell.h"

char	*terminal;
t_data	*data;

void	ft_kill()
{
	kill(data->cpid, SIGKILL);
}

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
	res[ft_strlen(res) - 1] = '\0';
	close(tubefd[0]);
	return (res);
}

void	ft_chooseaction(t_data *data, char **envp)
{
	t_parse *current;
	t_parse	*redir;

	current = ft_parse(terminal);
	redir = current;
	while (redir)
	{
		if (current->type == APPEND)
			redir_output("res", data, 1);
		if (current->type == OUTFILE)
			redir_output("res", data, 0);
		if (current->type == HEREDOC)
			ft_heredoc("fin");
		if (current->type == INFILE)
			redir_input("test", data);
		current = current->next;
	}
	if (data->infilefd != 0)
		close(data->infilefd);
	if (data->outfilefd != 1)
		close(data->outfilefd);
	exit(0);
}

void	ft_readterminal(t_data *data, char **envp)
{
	char *temp;

	temp = NULL;
	while (1)
	{
		data->cpid = 1;
		terminal = readline("\e[1;35mmi\e[1;34mni\e[1;32msh\e[1;33mel\e[1;31ml>\e[0;37m ");
		if (!terminal)
		{
			free(data);
			exit(0);
		}
		if (ft_strcmp(terminal, "exit") == 0)
		{
			free(terminal);
			return ;
		}
		data->cpid = fork();
		if (data->cpid == 0)
			ft_chooseaction(data, envp);
		waitpid(data->cpid, NULL, 0);
		if (ft_strcmp(terminal, temp) != 0)
		{
			add_history(terminal);
			free(temp);
			temp = terminal;
		}
		else
			free(terminal);
	}
}


int		main(int argc, char **argv, char **envp)
{
	//t_data	*data;

	(void) argc;
	(void) argv;
	signal(SIGINT, ft_kill);
	signal(SIGQUIT, SIG_IGN);
	data = malloc(sizeof(t_data));
	data->infilefd = 0;
	data->outfilefd = 1;
	data->ncmd = 0;
	ft_readterminal(data, envp);
	ft_parse(terminal);
	rl_clear_history();
	return (0);
}
