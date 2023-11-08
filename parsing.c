#include "minishell.h"

t_parse *ft_searchlastcmd(t_parse *current)
{
    while (current && current->type != CMD)
        current = current->previous;
    return (current);
}

int ft_isnl(char *token)
{
    int i;

    i = 0;
    while (token[i])
    {
        if (token[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

t_parse *ft_parse(char *terminal, t_data *data)
{
    t_parse *first;
    t_parse *current;
    t_parse *temp;
    char    *token;
    char    *terminal2;
    int     i;

    i = 0;
    terminal2 = ft_add_space_before(terminal);
    ft_check_quote(terminal2);
    first = malloc(sizeof(t_parse));
    data->pipe_detector = 1;
    current = first;
    current->previous = NULL;
    token = ft_strtok(data, terminal2);
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
                {
                    ft_exiterror("Minishell : parse error near '|'\n");
                    return (NULL);
                }
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
            else if (ft_isnl(token) == 1)
            {
                current = current->previous;
                free(current->next);
                current->next = NULL;
                while (current->type != HDCOMPLET)
                    current = current->previous;
                current->args = ft_realloc(current->args, token);
                while (current->next)
                    current = current->next;
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
        token = ft_strtok(data, terminal2);
        terminal2 = ft_cut_terminal(terminal2, token);
    }
    current->previous->next = NULL;
    free(current);
    free(terminal2);
    return (first);
}

int main(int argc, char **argv, char **envp)
{
    t_data  *data;
    t_parse *test;
    t_parse *temp;
    int i;

    data = malloc(sizeof(t_data));
    data->ncmd = 0;
    i = 0;
	while (envp[i])
		i++;
	data->envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp[i] = NULL;
    data->status = 0;
    data->parse = ft_parse("ls||wc", data);
    test = data->parse;
    while(data->parse)
    {
        printf("Type : %d\n", data->parse->type);
        i = 0;
        while(data->parse->args[i])
        {
            printf("%s", data->parse->args[i]);
            if (data->parse->args[i + 1])
                printf("\n");
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
    i = 0;
    while (data->envp[i])
    {
        free(data->envp[i]);
        i++;
    }
    free(data->envp);
    free(data);
    return (0);
}
