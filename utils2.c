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

char    *ft_cut_terminal(char *terminal, char *token)
{
    char    *newterminal;
    int start;
    int tokenlen;
    int i;

    start = 0;
    tokenlen = ft_strlen(token);
    i = 0;
    while (terminal[start] == ' ')
        start++;
    newterminal = (char *)malloc(sizeof(char) * ft_strlen(terminal) - start - tokenlen + 1);
    if (newterminal == 0)
        return (NULL);
    while (terminal)
    {
        newterminal[i] = terminal[start + tokenlen];
        i++;
        start++;
    }
    newterminal[i] = '\0';
    return (newterminal);
}

void    ft_realloc(char ***args, char *token)
{
    int current_size;
    int i;
    char    **new_args;

    current_size = 0;
    i = 0;
    while ((*args)[current_size] != NULL)
        current_size++;
    new_args = malloc(sizeof(char*) * (current_size + 2));
    if (new_args == NULL)
        ft_exiterror("Erreur d'allocation mémoire\n");
    while (*args)
    {
        new_args[i] = (*args)[i];
        i++;
    }
    new_args[i] = token;
    new_args[i + 1] = NULL;
    free(*args);
    *args = new_args;
}
