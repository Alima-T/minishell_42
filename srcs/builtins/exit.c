/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:17:26 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/09 18:32:45 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to terminate the shell
int	builtin_exit(int ac, char *av[])
{
	int	exit_status;

	if (ac > 2)
	{
		// too many args
		printf("exit: too many arguments\n");
		return (1);
	}
	if (ac == 2)
	{
		if (!ft_isnum(av[1]))
		{
			// Non-numeric argument
			printf("exit: %s: numeric argument required\n", av[1]);
			exit(255);
		}
		exit_status = ft_atoi(av[1]);
	}
	else
		exit_status = *get_exit_status();
	// print exit message and exit the shell with the provided status code
	printf("exit\n");
	exit(exit_status);
}
