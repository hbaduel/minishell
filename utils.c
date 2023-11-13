#include "minishell.h"

int		ft_exitperror(char *str)
{
	if (str)
		perror(str);
	return(0);
}

int		ft_exiterror(char *str)
{
	if (str)
		ft_putstr_fd(str, 1);
	return(0);
}

t_parse	*ft_free_parse(t_parse *parse)
{
	t_parse	*temp;
	int		i;

	while (parse)
	{
		i = 0;
		while (parse->args[i])
		{
			free(parse->args[i]);
			i++;
		}
		free(parse->args);
		temp = parse;
		parse = parse->next;
		free(temp);
	}
	return (NULL);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])

	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, int dofree)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	if (s1 && dofree == 1)
		free(s1);
	return (res);
}

void	ft_freedoubletab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n - 1 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
