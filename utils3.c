#include "minishell.h"

void    ft_strncpy(char *dest, char *src, int n)
{
    if (n <= 0 || *src == '\0')
        *dest = '\0';
    else
    {
        *dest = *src;
        ft_strncpy(dest + 1, src + 1, n - 1);
    }
}

char	*ft_strcpy(char *s1, char *s2)
{
	int i = 0;

	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char    *ft_add_space_before(char *str)
{
    int     i;
    char    *modified_str;
    char    *new_str;
    char    quote;

    i = 0;
    modified_str = ft_strdup(str);
    while (modified_str[i]) //before
    {
        if (modified_str[i] == '\'' || modified_str[i] == '"')
        {
            quote = modified_str[i];
            i++;
            while (modified_str[i] != quote && modified_str[i])
                i++;
        }
        else if (((modified_str[i] == '|') && modified_str[i - 1] != ' ')\
        || ((modified_str[i] == '<') && (modified_str[i - 1] != '<'))\
        || (modified_str[i] == '-')\
        || ((modified_str[i] == '>') && (modified_str[i - 1] != '>')))
        {
            new_str = malloc(strlen(modified_str) + 2);
            ft_strncpy(new_str, modified_str, i);
            new_str[i] = ' ';
            ft_strcpy(new_str + i + 1, modified_str + i);
            free(modified_str);
            modified_str = new_str;
            i += 2;
        }
        i++;
    }
    i = 0;
    while (modified_str[i]) //after
    {
        if (modified_str[i] == '\'' || modified_str[i] == '"')
        {
            quote = modified_str[i];
            i++;
            while (modified_str[i] != quote && modified_str[i])
                i++;
        }
        else if (((modified_str[i] == '|') && modified_str[i + 1] != ' ')\
        || ((modified_str[i] == '<') && (modified_str[i + 1] != '<'))\
        || ((modified_str[i] == '>') && (modified_str[i + 1] != '>')))
        {
            new_str = malloc(strlen(modified_str) + 2);
            ft_strncpy(new_str, modified_str, i + 1);
            new_str[i + 1] = ' ';
            ft_strcpy(new_str + i + 2, modified_str + i + 1);
            free(modified_str);
            modified_str = new_str;
        }
        i++;
    }
    return (modified_str);
}

char    *ft_envvalue(char *env, int start)
{
    char    *res;
    int     end;
    int     i;

    end = start;
    while (env[end])
        end++;
    res = malloc(sizeof(char) * (end - start + 1));
    i = 0;
    while (env[start])
    {
        res[i] = env[start];
        i++;
        start++;
    }
    res[i] = '\0';
    return (res);
}

char    *ft_getenvname(char *str)
{
    char    *res;
    int     i;

    i = 0;
    while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '=')
        i++;
    res = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '=')
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

char    *ft_getenv(char **envp, char *name, int *k)
{
    int     i;
    int     j;

    i = 0;
    *k += ft_strlen(name) + 1;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] == name[j] && name[j] && envp[i][j])
            j++;
        if (envp[i][j] == '=' && envp[i][j + 1] && name[j] == '\0')
        {
            free(name);
            return (ft_envvalue(envp[i], j + 1));
        }
        i++;
    }
    free(name);
    return (NULL);
}

char    *ft_remove_space(char *token)
{
    char *read_ptr;
    char *write_ptr;
    char *new_token;

    read_ptr = token;
    write_ptr = token;
    while (*read_ptr)
    {
        if (*read_ptr != ' ')
        {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
    if (write_ptr != token)
    {
        new_token = (char *)malloc(strlen(token) + 1);
        ft_strcpy(new_token, token);
        free(token);
        token = new_token;
    }
    return (token);
}

