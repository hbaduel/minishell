#include "minishell.h"

void	ft_interpret_dollar(char *str, int idx)
{
	printf("gestion du dolls");
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
	// printf("%d --- %c\n", inside_quote, quote);

	while (str[i])
	{
		if (str[i] == quote)
			inside_quote += 1;
		i++;
	}
	// printf("%d --- %c\n", inside_quote, quote);
	if (inside_quote % 2 != 0)
		ft_exiterror("Error : quotes have to be closed");
	else if (inside_quote % 2 == 0 && (quote == 34))
		ft_check_dollar(str, idx);
	return (&str[i + 1]);
}



void	ft_check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)			//simple quote
		{
			ft_quote(str, i, 39);
			break;
		}
		else if (str[i] == 34)		//double quote
		{
			ft_quote(str, i, 34);
			break;
		}
		else if (str[i] == '(' || str[i] == '{')
			ft_exiterror("Error : '()' and '{}' are not interpreted\n");		// parenthese et vaccolade
		i++;
	}
}
