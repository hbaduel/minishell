/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:32:41 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/08 13:56:52 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_lennumb(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb > 9)
	{
		len++;
		nb /= 10;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		isnegative;
	char	*ptr;
	long	nb;

	nb = n;
	isnegative = 0;
	len = ft_lennumb(nb);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb *= -1;
		isnegative = 1;
	}
	while (len - 1 >= isnegative)
	{
		ptr[len - 1] = nb % 10 + 48;
		nb /= 10;
		len--;
	}
	return (ptr);
}
