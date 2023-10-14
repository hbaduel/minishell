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
            while (current->args[i] != NULL)
            {
                printf("Argument %d: %s\n", i, current->args[i]);
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
    ft_cut_terminal(terminal, token);
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
            current->args = malloc(sizeof(char *) * 2);
            current->args[0] = ft_strdup(">");
            current->args[1] = NULL;
        }
        else if (ft_strcmp(token, "<<") == 0)
        {
            current->type = HEREDOC;
            current->args = malloc(sizeof(char *) * 2);
            current->args[0] = ft_strdup("<<");
            current->args[1] = NULL;
        }
        else if (ft_strcmp(token, ">>") == 0)
        {
            current->type = APPEND;
            current->args = malloc(sizeof(char *) * 2);
            current->args[0] = ft_strdup(">>");
            current->args[1] = NULL;
        }
        else if (ft_strcmp(token, "|") == 0)
        {
            current->type = PIPE;
            current->args = malloc(sizeof(char *) * 2);
            current->data->ncmd += 1;
            current->args[0] = ft_strdup("|");
            current->args[1] = NULL;
        }
        else
        {
            if (current->previous->type == CMD)
            {
                ft_realloc(&current->previous->args, token);
                current->previous->args[1] = ft_strdup(token);
                current->args[2] = NULL;
            }
            else if (current->previous->type == INFILE)
            {
                current->type = INFILE;
                current->args = malloc(sizeof(char *) * 2);
                current->args[0] = ft_strdup(token);
                current->args[1] = NULL;

            }
            else if (current->previous->type == OUTFILE)
            {
                current->type = OUTFILE;
                current->args = malloc(sizeof(char *) * 2);
                current->args[0] = ft_strdup(token);
                current->args[1] = NULL;
            }
            else if (current->previous->type == HEREDOC)
            {
                current->type = HEREDOC;
                current->args = malloc(sizeof(char *) * 2);
                current->args[0] = ft_strdup(token);
                current->args[1] = NULL;
            }
            else if (current->previous->type == APPEND)
            {
                current->type = APPEND;
                current->args = malloc(sizeof(char *) * 2);
                current->args[0] = ft_strdup(token);
                current->args[1] = NULL;
            }
            else
            current->type = CMD;
            current->args = malloc(sizeof(char *) * 2);
            current->args[0] = ft_strdup(token);
            current->args[1] = NULL;
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

// int main(void)
// {
//     t_data  data;
//     int i;

//     data.parse = ft_parse("< test grep test");
//     // while(data.parse)
//     // {
//     //     printf("Type : %d\n", data.parse->type);
//     //     i = 0;
//     //     while(data.parse->args[i])
//     //     {
//     //         printf("%s\n", data.parse->args[i]);
//     //         i++;
//     //     }
//     //     data.parse = data.parse->next;
//     // }
//     return (0);
// }
