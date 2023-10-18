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

char    *ft_add_space_before(char *str, int idx)
{
    int     i;
    char    *modified_str;
    char    *new_str;

    i = idx;
    modified_str = ft_strdup(str);
    while (str[i])
    {
        if ((str[i] == '|'))
        {
            new_str = malloc(strlen(modified_str) + 2);
            ft_strncpy(new_str, modified_str, i);
            new_str[i] = ' ';
            printf("NEWSTR : %s\n", new_str);
            strcpy(new_str + i, str + i);
            free(modified_str);
            modified_str = new_str;
            printf("MODIFIED STR 2 : %s\n", modified_str);
            // ft_add_space_before(modified_str, i);
        }
        i++;
    }
    printf("NEWSTR : %s\n", modified_str);
    return modified_str;
}
