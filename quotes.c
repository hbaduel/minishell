#include "minishell.h"

void	ft_interpret_dollar(char *str, int idx)
{
<<<<<<< HEAD
	printf("gestion du dolls");
=======
	while (str[idx])
	{
		// gerer les differents cas du $ entre double quote. jai vraiment la flemme la...
		printf("on est bien dans la gestion du DOLLS magueule\n");
	}
>>>>>>> 8690c9241e4e1dc90f4738d33b4af52e3f3c665b
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

char	*ft_check_dollar(char *str, int idx)
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
	return (str);
}

char	*ft_remove_quote(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			str[i] = ' ';
		i++;
	}
	return (str);
}

char	*ft_quote(char *str, int idx, char quote)
{
	int	i;
	int	inside_quote;

<<<<<<< HEAD
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
=======
	inside_quote = 0;
	i = idx;
	// printf("pas dans la boucle\n");
	while (str[i])
	{

		if (str[i] == quote)
			inside_quote += 1;
		// printf("%c ->> ", str[i]);
		// printf("%d\n",inside_quote);
		i++;
	}

	if (inside_quote % 2 == 0 && (quote == 39) && inside_quote != 0)		//simple quotes
	{
		str = ft_remove_quote(str, quote);
		printf("simple quote\n");
	}
	else if (inside_quote % 2 == 0 && (quote == 34) && inside_quote != 0)		//double quotes
	{
		printf("double quote\n");
		str = ft_remove_quote(str, quote);
		// str = ft_check_dollar(str, idx);
	}
	else if (inside_quote % 2 != 0)
		ft_exiterror("Error : quotes have to be closed");
	// printf("%s\n", str);
	return (str);
}

char	*ft_check_quote(char *str)
>>>>>>> 8690c9241e4e1dc90f4738d33b4af52e3f3c665b
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)			//simple quote
		{
			ft_quote(str, i, 39);
<<<<<<< HEAD
=======
			i++;
>>>>>>> 8690c9241e4e1dc90f4738d33b4af52e3f3c665b
			break;
		}
		else if (str[i] == 34)		//double quote
		{
			ft_quote(str, i, 34);
<<<<<<< HEAD
			break;
		}
		else if (str[i] == '(' || str[i] == '{')
			ft_exiterror("Error : '()' and '{}' are not interpreted\n");		// parenthese et vaccolade
=======
			i++;
			break;
		}
		else if (str[i] == '(' || str[i] == '{' || str[i] == ')' || str[i] == '}')
					ft_exiterror("Error : '()' and '{}' are not interpreted\n");		// parenthese et vaccolade
>>>>>>> 8690c9241e4e1dc90f4738d33b4af52e3f3c665b
		i++;
	}
	// printf("str2 --> %s\n", str);
	return (str);
}
