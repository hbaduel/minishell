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
    char    *next_token;
    int     start;
    int     end;
    int     i;

    if (!str)
        return (NULL);
    start = 0;
    while (str[start] == delim && str[start])
        start++;
    if (str[start] == '\'' || str[start] == '"' || str[start] == '(' || str[start] == '{' || str[start] == ')' || str[start] == '}')
        ft_check_quote(str);
    if (str[start] == '\\' || str[start] == ';')
        ft_exiterror("Error : '\\' and ';' are not interpreted.\n");
    if (str[start] == '\0')
        return (NULL);
    end = start;
    if (str[start] == '\'')
    {
        while (str[end] != '\'' && str[end])
            end++;
    }
    else if (str[start] == '"')
    {
        while (str[end] != '"' && str[end])
            end++;
    }
    else
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

    if (!token)
    {
        free(terminal);
        return (NULL);
    }
    start = 0;
    while (terminal[start] == ' ')
        start++;
    if (!terminal[start])
    {
        free(terminal);
        return (NULL);
    }
    tokenlen = ft_strlen(token);
    newterminal = malloc(sizeof(char) * (ft_strlen(terminal) - start - tokenlen + 1));
    i = 0;
    while (terminal[start + tokenlen + i])
    {
        newterminal[i] = terminal[start + tokenlen + i];
        i++;
    }
    newterminal[i] = '\0';
    free(terminal);
    return (newterminal);
}

char   **ft_realloc(char **args, char *token)
{
    int current_size;
    int i;
    char    **new_args;

    current_size = 0;
    i = 0;
    while (args[current_size])
        current_size++;
    new_args = malloc(sizeof(char *) * (current_size + 2));
    while (args[i])
    {
        new_args[i] = args[i];
        i++;
    }
    new_args[i] = ft_strdup(token);
    new_args[i + 1] = NULL;
    free(args);
    return (new_args);
}
