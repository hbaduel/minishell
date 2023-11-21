/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:57:40 by hbaduel           #+#    #+#             */
/*   Updated: 2023/11/21 11:07:39 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signalhandler(int sig)
{
	kill(0, 0);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*ft_setupdisplay(t_data *data)
{
	char	*name;
	char	*res;

	name = ft_getenv(data->envp, 0, ft_name("USER"), NULL);
	if (name)
	{
		res = ft_strjoin("\e[1;36m", name, 0);
		free(name);
		res = ft_strjoin(res, "\e[1;37m", 1);
		res = ft_strjoin(res, " 💻 ", 1);
	}
	else
		res = NULL;
	res = ft_strjoin(res, \
" \e[1;35mmi\e[1;34mni\e[1;32msh\e[1;33mel\e[1;31ml▸ \e[0;37m", 1);
	return (res);
}

void	ft_setupdata(t_data *data, char **envp)
{
	int	i;

	data->status = 0;
	data->ncmd = 0;
	data->infilefd = 0;
	data->outfilefd = 1;
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
	data->display = ft_setupdisplay(data);
}

void	ft_putheader(void)
{
	ft_putstr_fd("\n\n\e[1;35m _   .-')\e[1;34m                 .-') _", 1);
	ft_putstr_fd("\e[1;32m          .-')    ('-. .-.\e[1;33m   (\'-.", 1);
	ft_putstr_fd("\e[1;31m                     ,---.\n", 1);
	ft_putstr_fd("\e[1;35m( '.( \e[1;37mOO\e[1;35m )_\e[1;34m          ", 1);
	ft_putstr_fd("    ( \e[1;37mOO\e[1;34m ) )\e[1;32m        ( \e[1;37m", 1);
	ft_putstr_fd("OO\e[1;32m ). ( \e[1;37mOO\e[1;32m )  /\e[1;33m _(  ", 1);
	ft_putstr_fd("\e[1;37mOO\e[1;33m)\e[1;31m                    |   |\n", 1);
	ft_putstr_fd("\e[1;35m ,--.   ,--.) ,-.-')\e[1;34m ,--./ ,--,' ,-.-')", 1);
	ft_putstr_fd("\e[1;32m (_)---\\_),--. ,--.\e[1;33m(,------.,--.      ", 1);
	ft_putstr_fd("\e[1;31m,--.     |   |\n", 1);
	ft_putstr_fd("\e[1;35m |   `.'   |  |  |\e[1;37mOO\e[1;35m)\e[1;34m|  ", 1);
	ft_putstr_fd(" \\ |  |\\ |  |\e[1;37mOO\e[1;34m)\e[1;32m/    _ | |   |", 1);
	ft_putstr_fd("|  |\e[1;33m |  .---'|  |.-')  \e[1;31m|  |.-') |   |\n", 1);
	ft_putstr_fd("\e[1;35m |         |  |  |  \\\e[1;34m|    \\|  | )|  |", 1);
	ft_putstr_fd("  \\\e[1;32m\\  :` `. |   .|  |\e[1;33m |  |    |  | ", 1);
	ft_putstr_fd("\e[1;37mOO\e[1;33m ) \e[1;31m|  | \e[1;37mOO\e[1;31m )", 1);
	ft_putstr_fd("|   |\n", 1);
	ft_putstr_fd("\e[1;35m |  |'.'|  |  |  |(_/\e[1;34m|  .     |/ |  |(_/", 1);
	ft_putstr_fd("\e[1;32m '..`''.)|       |\e[1;33m(|  '--. |  |`-' | ", 1);
	ft_putstr_fd("\e[1;31m|  |`-' ||  .'\n", 1);
	ft_putstr_fd("\e[1;35m |  |   |  | ,|  |_.'\e[1;34m|  |\\    | ,|  |", 1);
	ft_putstr_fd("_.'\e[1;32m.-._)   \\|  .-.  |\e[1;33m |  .--'(|  '---.'", 1);
	ft_putstr_fd("\e[1;31m(|  '---.'`--'\n", 1);
	ft_putstr_fd("\e[1;35m |  |   |  |(_|  |\e[1;34m   |  | \\   |(_|  |  ", 1);
	ft_putstr_fd(" \e[1;32m\\       /|  | |  |\e[1;33m |  `---.|      |  ", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argc;
	(void) argv;
	ft_putheader();
	ft_putstr_fd("\e[1;31m|      | .--.\n", 1);
	ft_putstr_fd("\e[1;35m `--'   `--'  `--'\e[1;34m   `--'  `--'  `--'   ", 1);
	ft_putstr_fd(" \e[1;32m`-----' `--' `--' \e[1;33m`------'`------'  ", 1);
	ft_putstr_fd("\e[1;31m`------' '--'\n", 1);
	ft_putstr_fd("\e[1;36m                                             ", 1);
	ft_putstr_fd("                    \e[1;35mby hb\e[1;34madue\e[1;32ml ", 1);
	ft_putstr_fd("and \e[1;33maand\e[1;31mrieu 🍗\n\n\n", 1);
	signal(SIGINT, &ft_signalhandler);
	signal(SIGQUIT, SIG_IGN);
	data = malloc(sizeof(t_data));
	ft_setupdata(data, envp);
	ft_readterminal(data);
}
