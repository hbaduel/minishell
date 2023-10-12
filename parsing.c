#include "minishell.h"

t_parse     *ft_parse(char *terminal)
{
    t_parse *first = NULL;
    t_parse *current = NULL;    
    char *token;

    token = ft_strtok(terminal, " ");   
    while (token != NULL)
    {
        t_parse *new_node = (t_parse *)malloc(sizeof(t_parse));
        if (new_node == NULL)
        {
            perror("malloc");
            exit(1);
        }   
        if (ft_strcmp(token, ";") == 0)
        {
            new_node->type = SEPARATEUR;
        }
        else if (strcmp(token, ">") == 0)
        {
            new_node->type = OUTFILE;
            token = ft_strtok(NULL, " ");
            new_node->other = strdup(token); // nom du outgile
        }
        else if (ft_strcmp(token, "<") == 0)
        {
            new_node->type = INFILE;
            token = ft_strtok(NULL, " ");
            new_node->other = strdup(token); // nom infile
        }
        else
        {
            new_node->type = CMD;
            new_node->args = (char **)malloc(sizeof(char *));
            new_node->args[0] = strdup(token); // nom cmd
        }   
        new_node->next = NULL;  
        if (first == NULL)
        {
            first = new_node;
            current = new_node;
        }
        else
        {
            current->next = new_node;
            current = new_node;
        }
        token = ft_strtok(NULL, " ");
    }
    return first;
}

void ft_free_parse(t_parse *parse)
{
    t_parse *current = parse;
    while (current != NULL)
    {
        t_parse *next = current->next;
        if (current->type == CMD)
        {
            free(current->args[0]);
            free(current->args);
        }
        else if (current->type == INFILE || current->type == OUTFILE)
        {
            free(current->other);
        }
        free(current);
        current = next;
    }
}