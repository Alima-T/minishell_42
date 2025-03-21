/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:19:33 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 17:02:06 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_interact_ctrl_c(int signal)
{
	(void) signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	*get_exit_status() = 1;
}

void	sigs_interact_shell(void)
{
	struct sigaction	sa_int;
	struct termios		new_termios;

	sa_int.sa_handler = sig_interact_ctrl_c;
	sigemptyset(&sa_int.sa_mask);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, &sig_interact_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &new_termios);
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	sig_non_interact_quit(int signal)
{
	char	*nb;

	if (signal == SIGQUIT)
	{
		nb = ft_itoa(signal);
		ft_putstr_fd("ˆ\\Quit: ", STDERR_FILENO);
		ft_putendl_fd(nb, STDERR_FILENO);
		free(nb);
		nb = NULL;
		*get_exit_status() = 131;
	}
	if (signal == SIGINT)
		write(1, "^C\n", 3);
}

void	sig_non_interact_ctrl_c(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	*get_exit_status() = 130;
}

void	sigs_non_interact_shell(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = sig_non_interact_quit;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, sig_non_interact_quit);
}
