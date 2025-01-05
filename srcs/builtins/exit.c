/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:17:26 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/05 14:27:02 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to terminate the shell
int	builtin_exit(int ac, char *av[])
{
	int	exit_status;

	exit_status = 0;
	if (ac > 1)
		exit_status = ft_atoi(av[1]);
	// exit the shell with a status code of 0 (indicating success)
	exit(exit_status);
}
