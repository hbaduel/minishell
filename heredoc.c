#include "minishell.h"

extern char	*terminal;

int		ft_checklimiter()
{
	int	i;

	i = 0;
	while (terminal[i] != '\n' && terminal[i])
		i++;
	while (terminal[i])
	{

	}
}

char	*ft_heredoc(char *limiter)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("heredoc> ");
		terminal = ft_strjoin(terminal, "\n");
		terminal = ft_strjoin(terminal, heredoc);
		if (ft_strcmp(heredoc, limiter) == 0)
		{
			free(heredoc);
			return (NULL);
		}
		free(heredoc);
	}
	return (NULL);
}
