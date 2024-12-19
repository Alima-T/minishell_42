/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:05:23 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/19 14:12:58 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to remove an env variable
void	builtin_unset(char **args)
{
	const char	*error_message;

	if (args[1] == NULL)
	{
		error_message = "unset: missing arg\n";
		write(STDERR_FILENO, error_message, ft_strlen(error_message));
		return ;
	}
	// remove the specified env variable
	unsetenv(args[1]);
}
