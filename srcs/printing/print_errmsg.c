/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errmsg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:18:03 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 13:17:51 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_not_found_msg(char *message)
{
	ft_putstr_fd(BEGIN"minishell: "CLOSE, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
}

void	errmsg(char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	else
		perror("Error");
	*get_exit_status() = 128;
}
