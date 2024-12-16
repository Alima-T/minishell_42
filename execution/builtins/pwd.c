/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:43:15 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/16 14:26:29 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// function to print working directory
void	builtin_pwd(void)
{
	const char	*error_message;
	// buffer to hold the current working dir
	char		cwd[1024];

	// get the current working dir
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// write the current dir to st output
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		// error message for faillure
		error_message = "pwd: error retrieving current dir\n";
		// write error message to standard error
		write(STDERR_FILENO, error_message, ft_strlen(error_message));
	}
}
