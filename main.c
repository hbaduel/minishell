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
    t_parse *current = NULL;
	int	i = 0;
    while (current != NULL)
	{
        if (current->type == CMD)
		{
            printf("Command : ");
            if (current->args[i] != NULL)
			{
				ft_heredoc("fin");
				i++;
			}
			else
				redir_input("test", data);
			i++;
		}
		if (terminal[i] == '>')
		{
			if (terminal[i + 1] == '>')
			{
				redir_output("res", data, 1);
				i++;
			}
			else
				redir_output("res", data, 0);
			i++;
		}
		i++;
	}
	if (data->infilefd != 0)
		close(data->infilefd);
	if (data->outfilefd != 1)
		close(data->outfilefd);
	exit(0);
}

void	ft_readterminal(t_data *data, char **envp)
{
	pid_t	cpid;
    char *temp;
    t_parse *parse;

	temp = NULL;
    while (1)
	{
        terminal = readline("\e[1;35mmi\e[1;34mni\e[1;32msh\e[1;33mel\e[1;31ml>\e[0;37m ");
        if (ft_strcmp(terminal, "exit") == 0)
		{
			free(terminal);
			return ;
		}
		cpid = fork();
		if (cpid == 0)
			ft_chooseaction(data, envp);
		waitpid(cpid, NULL, 0);
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
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->infilefd = 0;
	data->outfilefd = 1;
	data->ncmd = 0;
	ft_readterminal(data, envp);
	ft_parse(terminal);
	rl_clear_history();
	return (0);
}
