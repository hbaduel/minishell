#include "minishell.h"

char	*terminal;

void	ft_kill()
{
	kill(0, 0);
	ft_putstr_fd("\n", 1);
}

void	ft_freeline(t_data *data, int which)
{
	t_parse	*temp;
	int		i;

	while (data->parse)
	{
		i = 0;
		while (data->parse->args[i])
		{
			free(data->parse->args[i]);
			i++;
		}
		free(data->parse->args);
		temp = data->parse;
		data->parse = data->parse->next;
		free(temp);
	}
	if (data->infilefd != 0)
		close(data->infilefd);
	if (data->outfilefd != 1)
		close(data->outfilefd);
	if (which == 1)
		free(data);
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
	pipe(tubefd);
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
	if (res[0])
		res[ft_strlen(res) - 1] = '\0';
	close(tubefd[0]);
	return (res);
}

void	ft_chooseaction(t_data *data, char **envp)
{
	if (data->infilefd != 0)
		dup2(data->infilefd, 0);
	if (data->ncmd == 1)
	{
		if (data->outfilefd != 1)
			dup2(data->outfilefd, 1);
		while (data->parse)
		{
			if (data->parse->type == CMD)
				ft_execcmd(data, data->parse->args, envp, data->outfilefd);
			data->parse = data->parse->next;
		}
	}
	else if (data->ncmd > 1)
		ft_pipe(data, data->parse, envp);
	// check s'il faut clear history dans un processus fils
	exit(0);
}

void	ft_readterminal(t_data *data, char **envp)
{
	char	*temp;
	pid_t	cpid;
	t_parse	*redir;
	int		operror;

	temp = NULL;
	while (1)
	{
		operror = 0;
		data->ncmd = 0;
		data->infilefd = 0;
		data->outfilefd = 1;
		terminal = readline("\e[1;35mmi\e[1;34mni\e[1;32msh\e[1;33mel\e[1;31ml>\e[0;37m ");
		if (!terminal)
		{
			free(data);
			exit(0);
		}
		if (terminal[0])
		{
			data->parse = ft_parse(terminal, data);
			redir = data->parse;
			while (redir)
			{
				if (redir->type == OUTCOMPLET)
					operror = ft_openfile(redir->args[1], data, 1);
				if (redir->type == APPENDCOMP)
					operror = ft_openfile(redir->args[1], data, 2);
				if (redir->type == HDCOMPLET)
					ft_heredoc(redir->args[1], data);
				if (redir->type == INCOMPLET)
					operror = ft_openfile(redir->args[1], data, 0);
				redir = redir->next;
				if (operror == 1)
					break ;
			}
			if (data->ncmd > 0 && operror == 0)
			{
				cpid = fork();
				if (cpid == 0)
					ft_chooseaction(data, envp);
				waitpid(cpid, NULL, 0);
			}
			ft_freeline(data, 0);
		}
		if (ft_strcmp(terminal, temp) != 0 && terminal[0])
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
	t_data	*data;

	(void) argc;
	(void) argv;
	signal(SIGINT, ft_kill);
	signal(SIGQUIT, SIG_IGN);
	data = malloc(sizeof(t_data));
	ft_readterminal(data, envp);
	rl_clear_history();
	return (0);
}
// segfault quand on prend l'historique d'un heredoc puis qu'on efface puis entrée
