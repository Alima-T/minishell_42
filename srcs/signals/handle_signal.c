/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:27:26 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/05 16:31:24 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
