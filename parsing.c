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
    t_parse *new;
    char    *token;
    char    *cmd;

    first = NULL;
    current = NULL;
    new = malloc(sizeof(t_parse));
    new->next = NULL;
    new->previous = NULL;
    new->args = NULL;
    token = ft_strtok(terminal, " ");
    while (token != NULL)
    {
        if (ft_strcmp(token, "<") == 0)
        {
            new->type = INFILE;
            new->args[0] = ft_strdup("<");
            new->args[1] = NULL;
        }
        else if (ft_strcmp(token, ">") == 0)
        {
            new->type = OUTFILE;
            new->args[0] = ft_strdup("<");
            new->args[1] = NULL;
        }
        else if (ft_strcmp(token, "<<") == 0)
        {
            new->type = HEREDOC;
            new->args[0] = ft_strdup("<<");
            new->args[1] = NULL;
        }
        else if (ft_strcmp(token, ">>") == 0)
        {
            new->type = APPEND;
            new->args[0] = ft_strdup(">>");
            new->args[1] = NULL;
        }
        else if (ft_strcmp(token, "|") == 0)
        {
            new->type = PIPE;
            new->data->ncmd += 1;
            new->args[0] = ft_strdup("|");
            new->args[1] = NULL;
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
                new->type = INFILE;
                new->args[0] = ft_strdup(token);
                printf("%s", new->args[0]);

            }
            else if (current->previous->type == OUTFILE)
            {
                new->type = OUTFILE;
                new->args[0] = ft_strdup(token);
                printf("%s", new->args[0]);
            }
            else if (current->previous->type == HEREDOC)
            {
                new->type = HEREDOC;
                new->args[0] = ft_strdup(token);
                printf("%s", new->args[0]);
            }
            else if (current->previous->type == APPEND)
            {
                new->type = APPEND;
                new->args[0] = ft_strdup(token);
                printf("%s", new->args[0]);
            }
            else
            new->type = CMD;
            new->args[0] = ft_strdup(token);
            printf("%s", new->args[0]);
        }
        if (current == NULL)
            first = new;
        else
            new = current->next;
        current = new;
        token = ft_strtok(NULL, " ");
    }
    return (first);
}
