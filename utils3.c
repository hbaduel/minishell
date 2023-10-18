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

    i = 0;
    modified_str = ft_strdup(str);
    while (modified_str[i]) //before
    {
        if ((modified_str[i] == '|') && modified_str[i - 1] != ' ')
        {
            new_str = malloc(strlen(modified_str) + 2);
            ft_strncpy(new_str, modified_str, i);
            new_str[i] = ' ';
            strcpy(new_str + i + 1, modified_str + i);
            free(modified_str);
            modified_str = new_str;
            i++;
        }
        i++;
    }
    i = 0;
    while (modified_str[i]) //after
    {
        if ((modified_str[i] == '|') && modified_str[i + 1] != ' ')
        {
            new_str = malloc(strlen(modified_str) + 2);
            ft_strncpy(new_str, modified_str, i + 1);
            new_str[i + 1] = ' ';
            strcpy(new_str + i + 2, modified_str + i + 1);
            free(modified_str);
            modified_str = new_str;
        }
        i++;
    }
    return (modified_str);
}
