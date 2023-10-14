#include "minishell.h"

void ft_print_tokens(t_parse *parse)
{
    t_parse *current = parse;
    while (current != NULL)
    {
        if (current->type == CMD && current->args != NULL)
        {
            char **args = current->args;
            printf("Command Type: CMD\n");
            int i = 0;
            while (args[i] != NULL)
            {
                printf("Argument %d: %s\n", i, args[i]);
                i++;
            }
        }
        else
        {
            printf("Type: %d\n", current->type);
            printf("Argument: %s\n", current->args[0]);
        }
        current = current->next;
    }
}



t_parse *ft_parse(char *terminal)
{
    t_parse *first;
    t_parse *current;
    char    *token;
    char    *cmd;

    first = malloc(sizeof(t_parse));
    current = first;
    current->previous = NULL;
    token = ft_strtok(terminal, ' ');
    while (token != NULL)
    {
        if (ft_strcmp(token, "<") == 0)
        {
            current->type = INFILE;
            current->args = malloc(sizeof(char *) * 2);
            current->args[0] = ft_strdup("<");
            current->args[1] = NULL;
        }
        else if (ft_strcmp(token, ">") == 0)
        {
            current->type = OUTFILE;
            current->args[0] = ft_strdup(">");
            current->args[1] = NULL;
        }
        else if (ft_strcmp(token, "<<") == 0)
        {
            current->type = HEREDOC;
            current->args[0] = ft_strdup("<<");
            current->args[1] = NULL;
        }
        else if (ft_strcmp(token, ">>") == 0)
        {
            current->type = APPEND;
            current->args[0] = ft_strdup(">>");
            current->args[1] = NULL;
        }
        else if (ft_strcmp(token, "|") == 0)
        {
            current->type = PIPE;
            current->data->ncmd += 1;
            current->args[0] = ft_strdup("|");
            current->args[1] = NULL;
        }
        else
        {
            if (current->previous->type == CMD)
            {
                current->previous->args[1] = ft_strdup(token);
                printf("%s", current->previous->args[1]);
            }
            else if (current->previous->type == INFILE)
            {
                current->type = INFILE;
                current->args[0] = ft_strdup(token);
                printf("%s", current->args[0]);

            }
            else if (current->previous->type == OUTFILE)
            {
                current->type = OUTFILE;
                current->args[0] = ft_strdup(token);
                printf("%s", current->args[0]);
            }
            else if (current->previous->type == HEREDOC)
            {
                current->type = HEREDOC;
                current->args[0] = ft_strdup(token);
                printf("%s", current->args[0]);
            }
            else if (current->previous->type == APPEND)
            {
                current->type = APPEND;
                current->args[0] = ft_strdup(token);
                printf("%s", current->args[0]);
            }
            else
            current->type = CMD;
            current->args[0] = ft_strdup(token);
            printf("%s", current->args[0]);
        }
        current->next = malloc(sizeof(t_parse));
        current->next->previous = current;
        current = current->next;
        token = ft_strtok(terminal, ' ');
    }
    current->previous->next = NULL;
    free(current);
    return (first);
}
int main(void)
{
    t_data  data;
    int i;

    data.parse = ft_parse("< test grep test");
    // while(data.parse)
    // {
    //     printf("Type : %d\n", data.parse->type);
    //     i = 0;
    //     while(data.parse->args[i])
    //     {
    //         printf("%s\n", data.parse->args[i]);
    //         i++;
    //     }
    //     data.parse = data.parse->next;
    // }
    return (0);
}
