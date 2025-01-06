/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:17:26 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/06 15:03:26 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to terminate the shell
int	builtin_exit(int ac, char *av[])
{
	int	get_exit_status;

	get_exit_status = 0;
	if (ac > 1)
		get_exit_status = ft_atoi(av[1]);
	// exit the shell with a status code of 0 (indicating success)
	exit(get_exit_status);
}
