#include "minishell.h"

void	ft_interpret_dollar(char *str, int idx)
{
	while (str[idx])
	{
		// gerer les differents ccas du $ entre double quote. jai vraiment la flemme la...
	}
}

char	ft_strchr(char *s, char c, char bol)
{
	while (*s)
	{
		if (*s == c)
			return (c);
		s++;
	}
	return (c);
}

void	ft_check_dollar(char *str, int idx)
{
	char	dollar;
	char	doll_in_quotes;
	int	i;

	dollar = '$';
	doll_in_quotes = 0;
	i = idx;
	while (str[i])
	{
		if (!ft_strchr(str, dollar, doll_in_quotes))
			ft_interpret_dollar(str, idx);
		i++;
	}
}

char	*ft_quote(char *str, int idx, char quote)
{
	int	inside_quote;
	int	i;

	inside_quote = 1;
	i = idx + 1;
	idx++;
	if (quote == '\'' || quote == '\"')
	{
		while ((str[i] != quote || str[i]))
		{
			if (str[i] == quote)
				inside_quote += 1;
			i++;
		}
	}
	else
	{
		if (quote == '(')
		{
			while (str[i])
			{
				if (str[i] == ')')
					inside_quote += 1;
				i++;
			}
		}
		if (quote == '{')
		{
			while (str[i])
			{
				if (str[i] == '}')
					inside_quote += 1;
				i++;
			}
		}
	}
	if (inside_quote % 2 != 0)
		ft_exiterror("Error : quotes have to be closed");
	if (inside_quote % 2 == 0 && (quote == '\"'))
		ft_check_dollar(str, idx);
	return (str);
}

void	ft_check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')			//simple quote 
			ft_quote(str, i, '\'');
		else if (str[i] == '\"')		//double quote
			ft_quote(str, i, '\"');
		else if (str[i] == '(')
			ft_quote(str, i, '(');		// parenthese
		if (str[i] == '{')
			ft_quote(str, i, '{');		//accolade
		i++;
	}
}