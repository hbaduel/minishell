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

char    *ft_strtok(char *str, char *delim)
{
    char    *next_token;  // Pointeur pour stocker l'état entre les appels.
    char    *token_start;

    next_token = NULL;
    if (str != NULL)
        next_token = str;
    else if (next_token == NULL)
        return NULL;
    while (*next_token != '\0' && strchr(delim, *next_token) != NULL)
        next_token++;
    if (*next_token == '\0')
    {
        next_token = NULL;
        return NULL;
    }
    token_start = next_token;
    while (*next_token != '\0' && strchr(delim, *next_token) == NULL)
        next_token++;
    if (*next_token != '\0')
    {
        *next_token = '\0';  // Marque la fin du token.
        next_token++;
    }
    return token_start;
}
