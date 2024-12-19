/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:17:26 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/19 15:55:51 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// function to terminate the shell
void	builtin_exit(void)
{
	// exit the shell with a status code of 0 (indicating success)
	exit(0);
}
