#include "minishell.h"

char	*ft_strdup(char *s)
{
	char	*str;
	int     i;

    if (!s)
        return (NULL);
	i = 0;
	str = malloc (sizeof(char) * (ft_strlen(s) + 1));
	while (s[i])
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
	return (str);
}

// debut fichier token

int ft_tokensize(t_data *data, char *str, char delim)
{
    char    *env;
    int size;
    int i;

    size = 0;
    i = 0;
    while (str[i] != delim && str[i])
    {
        if (str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\0'\
        && str[i + 1] != '$') && delim != '\'')
        {
            env = ft_getenv(data->envp, data->status, ft_getenvname(&str[i + 1]), &i);
            size += ft_strlen(env);
            free(env);
        }
        else
        {
            i++;
            size++;
        }
    }
    return (size + 1);
}

void    ft_putenv(char *nexttoken, char *env, int *j)
{
    int     k;

    k = 0;
    if (!env)
        return ;
    while (env[k])
    {
        nexttoken[*j] = env[k];
        k++;
        *j += 1;
    }
    free(env);
}

char    *ft_tokenquote(t_data *data, char *str, char delim)
{
    char    *nexttoken;
    int     i;
    int     j;

    nexttoken = malloc(sizeof(char) * (ft_tokensize(data, str, delim)));
    i = 0;
    j = 0;
    while (str[i] != delim && str[i])
    {
        if (delim != '\'' && str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\0'\
        && str[i + 1] != '$'))
            ft_putenv(nexttoken, ft_getenv(data->envp, data->status, ft_getenvname(&str[i + 1]), &i), &j);
        else
        {
            nexttoken[j] = str[i];
            j++;
            i++;
        }
    }
    nexttoken[j] = '\0';
    return (nexttoken);
}

char    *ft_quotemidtoken(t_data *data, char *nexttoken, char *str, int j)
{
    char    *temp;
    char    delim;
    int     i;

    i = 1;
    delim = str[0];
    nexttoken[j] = '\0';
    temp = ft_tokenquote(data, &str[i], str[0]);
    nexttoken = ft_strjoin(nexttoken, temp, 1);
    free(temp);
    while (str[i] != delim)
        i++;
    if (str[i + 1] != ' ' && str[i + 1])
    {
        temp = ft_tokennoquote(data, &str[i + 1]);
        nexttoken = ft_strjoin(nexttoken, temp, 1);
        free(temp);
    }
    return (nexttoken);
}

char    *ft_tokennoquote(t_data *data, char *str)
{
    char    *nexttoken;
    int     i;
    int     j;

    nexttoken = malloc(sizeof(char) * (ft_tokensize(data, str, ' ')));
    i = 0;
    j = 0;
    while (str[i] != ' ' && str[i])
    {
        if (str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\0'\
        && str[i + 1] != '$'))
            ft_putenv(nexttoken, ft_getenv(data->envp, data->status, ft_getenvname(&str[i + 1]), &i), &j);
        else if (str[i] == '\'' || str[i] == '\"')
            return (ft_quotemidtoken(data, nexttoken, &str[i], j));
        else
        {
            nexttoken[j] = str[i];
            j++;
            i++;
        }
    }
    nexttoken[j] = '\0';
    return (nexttoken);
}

char    *ft_strtok(t_data *data, char *str)
{
    int     start;
    int     end;
    int     i;

    start = 0;
    end = 0;
    i = 0;
    while (str[start] == ' ' && str[start])
        start++;
    if (!str[start])
        return (NULL);
    if (str[start] == '\'' || str[start] == '"')
        return (ft_tokenquote(data, &str[start + 1], str[start]));
    else
        return (ft_tokennoquote(data, &str[start]));
}

// fin fichier quote

// new fichier quote

char    *ft_cutquote(char *terminal, char delim)
{
    char    *new;
    int     start;
    int     end;
    int     i;

    start = 0;
    while (terminal[start] != delim && terminal[start])
        start++;
    end = start;
    while (terminal[end])
        end++;
    new = malloc(sizeof(char) * (end - start + 1));
    start++;
    i = 0;
    while (start < end)
    {
        new[i] = terminal[start];
        start++;
        i++;
    }
    new[i] = '\0';
    return (new);
}

int     ft_cutsize(char *terminal, int *start, int *end)
{
    char    delim;

    *start = 0;
    *end = 0;
    while (terminal[*start] != ' ' && terminal[*start])
    {
        if (terminal[*start] == '\'' || terminal[*start] == '\"')
        {
            delim = terminal[*start];
            *start += 1;
            while (terminal[*start] != delim && terminal[*start])
                *start += 1;
        }
        *start += 1;
    }
    *end = *start;
    while (terminal[*end])
        *end += 1;
}

char    *ft_cutnoquote(char *terminal)
{
    char    *newterminal;
    int     start;
    int     end;
    int     i;

    ft_cutsize(terminal, &start, &end);
    newterminal = malloc(sizeof(char) * (end - start + 1));
    i = 0;
    while (start < end)
    {
        newterminal[i] = terminal[start];
        start++;
        i++;
    }
    newterminal[i] = '\0';
    return (newterminal);
}

char    *ft_cut_terminal(char *terminal, char *token)
{
    char    *newterminal;
    int     start;
    int     i;

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
    if (terminal[start] == '\'' || terminal[start] == '\"')
        newterminal = ft_cutquote(&terminal[start + 1], terminal[start]);
    else
        newterminal = ft_cutnoquote(&terminal[start]);
    free(terminal);
    return (newterminal);
}

// fin fichier quote

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
