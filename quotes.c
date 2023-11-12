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


// char	*ft_remove_quote(char *str, char quote)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == quote)
// 			str[i] = ' ';
// 		i++;
// 	}
// 	return (str);
// }

void	ft_quote(char *str, int idx, char quote)
{
	int	i;
	int	inside_quote;

	inside_quote = 1;
	i = idx + 1;
	while (str[i])
	{
		if (str[i] == quote)
			inside_quote += 1;
		i++;
	}
	if (inside_quote % 2 != 0)
		ft_exiterror("Error : quotes have to be closed");
}

// int	ft_dolls_is_ok(char *str)
// {
// 	int	i;
// 	int	dq;
// 	int	sq;

// 	i = 0;
// 	dq = -1;
// 	sq = -1;
// 	while (str[i] != '$')
// 	{
// 		if (str[i] == 34)
// 			dq = i;
// 		if (str[i] == 39)
// 			sq = i;
// 		i++;
// 	}
// 	if (sq > dq)
// 		return (0);
// 	return (1);
// }

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
		else if (str[i] == '(' || str[i] == '{' || str[i] == ')' || str[i] == '}')
			ft_exiterror("Error : '()' and '{}' are not interpreted\n");		// parenthese et vaccolade
		i++;
	}
	return (str);
}
