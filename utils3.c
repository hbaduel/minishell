#include "minishell.h"

void ft_strncpy(char *dest, char *src, size_t n)
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

char *ft_add_space_before_pipe(char *str)
{
        int pipe_index;
        int i;
        char *modified_str;

        i = 0;
        pipe_index = 0;
        while (str[i])
        {
                if (str[i] == '|')
                {
                    pipe_index = i;
                    break;
                }
                i++;
        }
        if (pipe_index > 0)
        {
                modified_str = malloc(strlen(str) + 2);
                if (modified_str == NULL)
                    return NULL;
                ft_strncpy(modified_str, str, pipe_index);
                modified_str[pipe_index] = ' ';
                ft_strcpy(modified_str + pipe_index + 1, str + pipe_index);
                return modified_str;
        }
        else
                return (ft_strdup(str));   
}
