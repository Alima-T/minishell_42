/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:43:15 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/23 18:01:27 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Prints working directory.
 * @param
 * @return
 */
int	builtin_pwd(void)
{
	const char	*error_message;
	char		cwd[1024];

	// buffer to hold the current working dir
	// get the current working dir
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// write the current dir to st output
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else
	{
		// error message for faillure
		error_message = "pwd: error retrieving current dir\n";
		// write error message to standard error
		write(STDERR_FILENO, error_message, ft_strlen(error_message));
		return (1);
	}
}
