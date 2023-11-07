# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

char    *ft_strtok(char *str, char delim)
{
    char    *next_token;
    char    *temp;
    char    *result;
    int     start;
    int     end;
    int     i;

    next_token = NULL;
    temp = NULL;
    result = NULL;
    start = 0;
    end = 0;
    i = 0;
    if (!str)
        return (NULL);
    while (str[start] == ' ' && str[start])
        start++;
    if (str[start] == '\'' || str[start] == '"')
    {
        delim = str[start];
        start++;
        end = start;
        while (str[end] != delim && str[end])
            end++;
        if (str[end] == delim)
        {
            temp = malloc(end - start -1);
            while (start < end)
            {
                temp[i] = str[start];
                start++;
                i++;
            }
            // temp[i] = quote;
            temp[i] = '\0';
            // start = end + 1;
        }
    }
    else
    {
        end = start;
        while (str[end] != delim && str[end])
            end++;
        if (start != end)
        {
            next_token = malloc(end - start + 1);
            i = 0;
            while (start < end)
            {
                next_token[i] = str[start];
                start++;
                i++;
            }
            next_token[i] = '\0';
        }
    }
    if (temp && next_token)
    {
        result = malloc(strlen(temp) + strlen(next_token) + 1);
        free(temp);
        free(next_token);
        return (result);
    }
    else if (temp)
        return (temp);
    else if (next_token)
        return (next_token);
    else
        return (NULL);
}

int     main()
{
        char    *test1 = "echo test";
        char    *test2 = "echo 'test'";
        char    *test3 = "";

        printf("TEST1 : %s\n", ft_strtok(test1, ' '));
        printf("TEST2 : %s\n", ft_strtok(test2, ' '));
        printf("TEST3 : %s\n", ft_strtok(test3, ' '));

}