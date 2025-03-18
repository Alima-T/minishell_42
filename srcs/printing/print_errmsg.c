/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errmsg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:18:03 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/18 08:44:53 by aokhapki         ###   ########.fr       */
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