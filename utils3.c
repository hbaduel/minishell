#include "minishell.h"

void	ft_strncpy(char *dest, char *src, int n)
{
	if (n <= 0 || *src == '\0')
		*dest = '\0';
	else
	{
		*dest = *src;
		ft_strncpy(dest + 1, src + 1, n - 1);
	}
}

char	*ft_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_addspace(char *modifstr, int i, int plus)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(modifstr) + 2 + plus));
	ft_strncpy(res, modifstr, i + plus);
	res[i + plus] = ' ';
	ft_strcpy(res + i + 1 + plus, modifstr + i + plus);
	free(modifstr);
	return (res);
}

char	*ft_add_space_after(char *modified_str)
{
	char	quote;
	int		i;

	i = 0;
	while (modified_str[i])
	{
		if (modified_str[i] == '\'' || modified_str[i] == '"')
		{
			quote = modified_str[i];
			i++;
			while (modified_str[i] != quote && modified_str[i])
			    i++;
		}
		else if ((modified_str[i] == '|' && modified_str[i + 1] != ' ')\
		|| (modified_str[i] == '<' && modified_str[i + 1] != '<')\
		|| (modified_str[i] == '>' && modified_str[i + 1] != '>'))
		{
			modified_str = ft_addspace(modified_str, i, 1);
			i += 2;
		}
		i++;
	}
	return (modified_str);
}

char	*ft_add_space_before(char *modified_str)
{
	int		i;
	char	quote;

	i = 0;
	while (modified_str[i])
	{
		if (modified_str[i] == '\'' || modified_str[i] == '"')
		{
			quote = modified_str[i];
			i++;
			while (modified_str[i] != quote && modified_str[i])
				i++;
		}
		else if ((modified_str[i] == '|') && (i == 0 || modified_str[i - 1] != ' ')\
		|| (modified_str[i] == '<') && (i == 0 || (modified_str[i - 1] != '<'))\
		|| (modified_str[i] == '-')\
		|| ((modified_str[i] == '>') && (i == 0 || modified_str[i - 1] != '>')))
		{
			modified_str = ft_addspace(modified_str, i, 0);
			i++;
		}
		i++;
	}
	return (ft_add_space_after(modified_str));
}

char	*ft_envvalue(char *env, int start)
{
	char	*res;
	int		end;
	int		i;

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

char	*ft_getenvname(char *str)
{
	char	*res;
	int		i;

    i = 0;
    while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '=' &&  str[i] != '\t' && str[i] != '\n')
        i++;
    res = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '=' && str[i] != '\t' && str[i] != '\n')
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

char	*ft_getenv(char **envp, int status, char *name, int *k)
{
	int		i;
	int		j;

	i = 0;
	*k += ft_strlen(name) + 1;
	if (ft_strcmp(name, "?") == 0)
	{
		free(name);
		return (ft_itoa(status));
	}
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
