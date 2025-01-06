/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:27:26 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/06 14:45:11 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void sig_interact_ctrl_c(int signal)

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n[minishell ]$ ", STDERR_FILENO);
		*exit_status() = 130;
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		*exit_status() = 131;
	}
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
