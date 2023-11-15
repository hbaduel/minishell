/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:19:33 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/14 19:41:54 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_addspace(char *modifstr, int i, int plus)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(modifstr) + 2 + plus));
	ft_strncpy(res, modifstr, i + plus);
	res[i + plus] = ' ';
	ft_strcpy(res + i + 1 + plus, modifstr + i + plus);
	free(modifstr);
	return (res);
}

char	*ft_add_space_after(char *modified_str)
{
	char	quote;
	int		i;

	i = 0;
	while (modified_str[i])
	{
		if (modified_str[i] == '\'' || modified_str[i] == '"')
		{
			quote = modified_str[i];
			i++;
			while (modified_str[i] != quote && modified_str[i])
				i++;
		}
		else if ((modified_str[i] == '|' && modified_str[i + 1] != ' ') \
		|| (modified_str[i] == '<' && modified_str[i + 1] != '<') \
		|| (modified_str[i] == '>' && modified_str[i + 1] != '>'))
		{
			modified_str = ft_addspace(modified_str, i, 1);
			i += 2;
		}
		i++;
	}
	return (modified_str);
}

char	*ft_add_space_before(char *modified_str)
{
	int		i;
	char	quote;

	i = 0;
	while (modified_str[i])
	{
		if (modified_str[i] == '\'' || modified_str[i] == '"')
		{
			quote = modified_str[i];
			i++;
			while (modified_str[i] != quote && modified_str[i])
				i++;
		}
		else if ((modified_str[i] == '|') && \
		(i == 0 || modified_str[i - 1] != ' ') \
		|| (modified_str[i] == '<') && (i == 0 || (modified_str[i - 1] != '<')) \
		|| (modified_str[i] == '>') && (i == 0 || modified_str[i - 1] != '>'))
		{
			modified_str = ft_addspace(modified_str, i, 0);
			i++;
		}
		i++;
	}
	return (ft_add_space_after(modified_str));
}
