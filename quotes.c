#include "minishell.h"

char	*ft_strstr(char *haystack, char *needle)
{
	char	*h;
        char	*n;
	if (*needle == '\0')
        	return ((char *)haystack);

	while (*haystack != '\0')
	{
		h = haystack;
		n = needle;	
		while (*h != '\0' && *n != '\0' && *h == *n)
		{
		    h++;
		    n++;
		}
		if (*n == '\0')
		    return ((char *)haystack);
		haystack++;
	}
	return (NULL);
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
	// else if (inside_quote % 2 == 0 && (quote == 34))
	// 	ft_check_dollar(str, idx);
	return (&str[i + 1]);
}



char	*ft_check_quote(char *str)
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
	// printf("str2 --> %s\n", str);
	return (str);
}
