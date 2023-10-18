#include "minishell.h"

char    *ft_add_space(char *str)
{
    char    *new_str;
    int i;

    new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
    i = 0;
    while ((str[i] == '<' || str[i] == '>' || str[i] == '|' || str[i] == ' ') && str[i])
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = ' ';
    while (str[i])
    {
        new_str[i + 1] = str[i];
        i++;
    }
    new_str[i + 1] = '\0';
    free(str);
    return (new_str);
}

char    *ft_check_filename(char *str)
{
    int i;

    i = 0;
    while (str[i] == ' ')
        i++;
    if (str[i] != '>' && str[i] != '<' && str[i] != '|')
        return (str);
    if (str[i] == '|' && str[i + 1] == '|')
        return (NULL);
    while (str[i] == '<' || str[i] == '>' || str[i] == '|')
        i++;
    if (str[i] != ' ')
        str = ft_add_space(str);
    return (str);
}

t_parse *ft_searchlastcmd(t_parse *current)
{
    while (current && current->type != CMD)
        current = current->previous;
    return (current);
}

t_parse *ft_parse(char *terminal, t_data *data)
{
    t_parse *first;
    t_parse *current;
    t_parse *temp;
    char    *token;
    char    *terminal2;

    terminal = ft_add_space_before(terminal, 0);
    terminal2 = ft_strdup(terminal);
    first = malloc(sizeof(t_parse));
    data->pipe_detector = 1;
    current = first;
    current->previous = NULL;
    token = ft_strtok(&terminal2, ' ');
    terminal2 = ft_cut_terminal(terminal2, token);
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
                if (!current->previous || data->pipe_detector == 1)
                    ft_exiterror("Minishell : parse error near '|'\n");
                data->pipe_detector = 1;
                current = current->previous;
                free(current->next);
        }
        else
        {
            if (!current->previous)
            {
                current->type = CMD;
                current->args = malloc(sizeof(char *) * 2);
                current->args[0] = ft_strdup(token);
                current->args[1] = NULL;
                data->ncmd++;
                data->pipe_detector = 0;
            }
            else if (current->previous->type == INFILE)
            {
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
                current->type = INCOMPLET;
            }
            else if (current->previous->type == OUTFILE)
            {
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
                current->type = OUTCOMPLET;
            }
            else if (current->previous->type == HEREDOC)
            {
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
                current->type = HDCOMPLET;
            }
            else if (current->previous->type == APPEND)
            {
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
                current->type = APPENDCOMP;
            }
            else if (data->pipe_detector == 1)
            {
                current->type = CMD;
                current->args = malloc(sizeof(char *) * 2);
                current->args[0] = ft_strdup(token);
                current->args[1] = NULL;
                data->pipe_detector = 0;
                data->ncmd++;
            }
            else if (current->previous->type == CMD)
            {
                current->previous->args = ft_realloc(current->previous->args, token);
                current = current->previous;
                free(current->next);
            }
            else if ((current->previous->type >= 7 && current->previous->type <= 10) && data->pipe_detector == 0)
            {
                temp = ft_searchlastcmd(current);
                temp->args = ft_realloc(temp->args, token);
                current = current->previous;
                free(current->next);
            }
        }
        current->next = malloc(sizeof(t_parse));
        current->next->previous = current;
        current = current->next;
        free(token);
        token = ft_strtok(&terminal2, ' ');
        terminal2 = ft_cut_terminal(terminal2, token);
    }
    current->previous->next = NULL;
    free(current);
    free(terminal2);
    return (first);
}

int main(int argc, char **argv)
{
    t_data  *data;
    t_parse *test;
    t_parse *temp;
    int i;

    if (argc == 1)
        return (0);
    data = malloc(sizeof(t_data));
    data->ncmd = 0;
    data->parse = ft_parse(argv[1], data);
    test = data->parse;
    while(data->parse)
    {
        printf("Type : %d\n", data->parse->type);
        i = 0;
        while(data->parse->args[i])
        {
            printf("%s ", data->parse->args[i]);
            i++;
        }
        printf("\n");
        printf("\n");
        data->parse = data->parse->next;
    }
    printf("NCMD : %d\n", data->ncmd);
    while (test)
	{
		i = 0;
		while (test->args[i])
		{
			free(test->args[i]);
			i++;
		}
		free(test->args);
		temp = test;
		test = test->next;
		free(temp);
	}
    free(data);
    return (0);
}
