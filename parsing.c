#include "minishell.h"

// void ft_print_tokens(t_parse *parse)
// {
//     t_parse *current = parse;
//     while (current != NULL)
//     {
//         if (current->type == CMD && current->args != NULL)
//         {
//             char **args = current->args;
//             printf("Command Type: CMD\n");
//             int i = 0;
//             while (current->args[i] != NULL)
//             {
//                 printf("Argument %d: %s\n", i, current->args[i]);
//                 i++;
//             }
//         }
//         else
//         {
//             printf("Type: %d\n", current->type);
//             printf("Argument: %s\n", current->args[0]);
//         }
//         current = current->next;
//     }
// }

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
    terminal = ft_cut_terminal(terminal, token);
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
            current->args[0] = ft_strdup("|");
            current->args[1] = NULL;
        }
        else
        {
            if (!current->previous)
            {
                current->type = CMD;
                current->args = malloc(sizeof(char *) * 2);
                current->args[0] = ft_strdup(token);
                current->args[1] = NULL;
            }
            else if (current->previous->type == FILENAME || current->previous->type == PIPE)
            {
                current->type = CMD;
                current->args = malloc(sizeof(char *) * 2);
                current->args[0] = ft_strdup(token);
                current->args[1] = NULL;
            }
            else if (current->previous->type == CMD)
            {
                current->type = CMD;
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
            }
            else if (current->previous->type == INFILE)
            {
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
                current->type = FILENAME;
            }
            else if (current->previous->type == OUTFILE)
            {
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
                current->type = FILENAME;
            }
            else if (current->previous->type == HEREDOC)
            {
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
                current->type = FILENAME;
            }
            else if (current->previous->type == APPEND)
            {
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
                current->type = FILENAME;
            }
        }
        current->next = malloc(sizeof(t_parse));
        current->next->previous = current;
        current = current->next;
        free(token);
        token = ft_strtok(terminal, ' ');
        terminal = ft_cut_terminal(terminal, token);
    }
    current->previous->next = NULL;
    free(current);
    return (first);
}

// int main(int argc, char **argv)
// {
//     t_data  data;
//     t_parse *test;
//     t_parse *temp;
//     int i;

//     data.parse = ft_parse(ft_strdup(argv[1]));
//     test = data.parse;
//     while(data.parse)
//     {
//         printf("Type : %d\n", data.parse->type);
//         i = 0;
//         while(data.parse->args[i])
//         {
//             printf("%s ", data.parse->args[i]);
//             i++;
//         }
//         printf("\n");
//         data.parse = data.parse->next;
//     }
//     while(test)
//     {
//         i = 0;
//         while (test->args[i])
//         {
//             free(test->args[i]);
//             i++;
//         }
//         free(test->args);
//         temp = test;
//         test = test->next;
//         free(temp);
//     }
//     return (0);
// }
