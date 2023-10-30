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
	char	**path;
	char	*res;
	int		i;

	cmd = ft_strjoin("/", cmd, 0);
	i = 0;
	while (strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(&envp[i][5], ':');
	i = 0;
	while (path[i])
	{
		res = ft_strjoin(path[i], cmd, 0);
		if (access(res, R_OK) == 0)
		{
			ft_freedoubletab(path);
			free(cmd);
			return (res);
		}
		free(res);
		i++;
	}
	ft_freedoubletab(path);
	free(cmd);
	return (NULL);
}

void	ft_chooseaction(t_data *data)
{
	pid_t	cpid;
	int		didbuiltin;

	if (data->ncmd == 1)
	{
		while (data->parse->type != CMD)
			data->parse = data->parse->next;
		if (ft_cmdbuiltin(data, data->outfilefd, data->parse->args) == 1)
			return ;
		cpid = fork();
		if (cpid == 0)
		{
			if (data->infilefd != 0)
				dup2(data->infilefd, 0);
			if (data->outfilefd != 1)
				dup2(data->outfilefd, 1);
			ft_execcmd(data->parse->args, data->envp, data->outfilefd);
		}
		data->status = waitpid(cpid, NULL, 0);
	}
	else if (data->ncmd > 1)
		ft_pipe(data, data->parse);
	return ;
}

void	ft_readterminal(t_data *data)
{
	pid_t	cpid;
	t_parse	*redir;
	int		operror;

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
				ft_chooseaction(data);
			ft_freeline(data, 0);
			add_history(terminal);
		}
		free(terminal);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		i;

	(void) argc;
	(void) argv;
	signal(SIGINT, ft_kill);
	signal(SIGQUIT, SIG_IGN);
	data = malloc(sizeof(t_data));
	data->status = 0;
	i = 0;
	while (envp[i])
		i++;
	data->envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp[i] = NULL;
	ft_readterminal(data);
	rl_clear_history();
	return (0);
}
// segfault quand on prend l'historique d'un heredoc puis qu'on efface puis entrée
