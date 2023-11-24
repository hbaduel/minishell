/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:51:01 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/24 18:01:15 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signalquit(int sig)
{
	kill(0, 0);
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	else if (sig == SIGINT)
		write(1, "\n", 1);
}

void	ft_signalnewline(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
