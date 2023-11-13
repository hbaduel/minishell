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

int	ft_quote(char *str, int *i, char quote)
{
	*i += 1;
	while (str[*i] != quote && str[*i])
	{
		if (str[*i] == '\\' || str[*i] == ';')
		{
			ft_putstr_fd("Error : '\\' and ';' are not interpreted.\n", 1);
			return (1);
		}
		*i += 1;
	}
	if (!str[*i])
	{
		ft_putstr_fd("Error : quotes have to be closed.\n", 1);
		return (1);
	}
	return (0);
}

int	ft_check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			if (ft_quote(str, &i, str[i]) == 1)
			{
				free(str);
				return (1);
			}
		}
		else if (str[i] == '\\' || str[i] == ';')
		{
			free(str);
			ft_putstr_fd("Error : '\\' and ';' are not interpreted.\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}
