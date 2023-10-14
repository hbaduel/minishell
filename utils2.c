#include "minishell.h"

int ft_strlcpy(char *dest, char *src, int size)
{
	int    len;

	len = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[len] && len + 1 < size)
	{
		dest[len] = src[len];
		len++;
	}
	dest[len] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = malloc (sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

char    *ft_strtok(char *str, char delim)
{
    char    *next_token;  // Pointeur pour stocker l'état entre les appels.
    int     start;
    int     end;
    int     i;

    if (!str)
        return (NULL);
    start = 0;
    while (str[start] == delim && str[start])
        start++;
    if (str[start] == '\0')
        return (NULL);
    end = start;
    while (str[end] != delim && str[end])
        end++;
    next_token = malloc(sizeof(char) * (end - start + 1));
    i = 0;
    while (start < end)
    {
        next_token[i] = str[start];
        start++;
        i++;
    }
    next_token[i] = '\0';
    return (next_token);
}
