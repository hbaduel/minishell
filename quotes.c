#include "minishell.h"

char	*ft_quote(char *str, int idx, char quote)
{
	int	inside_quote;
	int	i;

	inside_quote = 1;
	i = idx + 1;
	idx++;
	while (str[i] != quote || str[i])
	{
		if (str[i] == quote)
			inside_quote += 1;
		i++;
	}
	if (inside_quote % 2 == 0)
	{
		while(idx != i)
		{
			// du coup faudra gerer les metacaracteres ici
		}
	}
	else
		ft_exiterror("Error : quotes cannot be used alone");
	return (str);
}

void	ft_parenthesis(char *str, int idx)
{

}

void	ft_brace(char *str, int idx)
{

}

void	ft_check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ft_quote(str, i, '\'');
		else if (str[i] == '\"')
			ft_quote(str, i, '\"');
		else if (str[i] == '(')
			ft_parenthesis(str, i);
		if (str[i] == '{')
			ft_brace(str, i);
		i++;
	}
}

int	main()
{
	ft_check_quote("Je suis ' un test ' est ce que ca marche");
	return (0);
}
