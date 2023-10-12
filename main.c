#include "minishell.h"

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

void print_tokens(t_parse *parse)
{
    t_parse *current = parse;
	int	i = 0;
    while (current != NULL)
	{
        if (current->type == CMD)
		{
            printf("Command : ");
            while (current->args[i] != NULL)
			{
                printf("%s ", current->args[i]);
				i++;
			}
        }
		else if (current->type == SEPARATEUR)
            printf("Séparateur : ;");
		else if (current->type == INFILE)
            printf("Fichier d'entrée : %s", current->other);
		else if (current->type == OUTFILE)
            printf("Fichier de sortie : %s", current->other);

        printf("\n");

        current = current->next;
    }
}

void	ft_readterminal()
{
    char *terminal;
    t_parse *parse;

    while (1)
	{
        terminal = readline("\e[1;35mmi\e[1;34mni\e[1;32msh\e[1;33mel\e[1;31ml>\e[0;37m ");
        if (ft_strcmp(terminal, "exit") == 0)
		{
            free(terminal);
            break;
        }
        add_history(terminal);
        parse = ft_parse(terminal);

		print_tokens(parse);
		
        // Ici on gere les commandes :S

        ft_free_parse(parse);
        free(terminal);
    }
}


int		main(int argc, char **argv, char **envp)
{
    ft_readterminal();
    rl_clear_history();
    return 0;
}
