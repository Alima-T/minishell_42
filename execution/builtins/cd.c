/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:17:00 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/16 14:26:43 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// changes the current working dir to the specified path
void	builtin_cd(char **args)
{
	const char	*error_message;

	// checks if an arg is provided; if not, writes an error message to STDERR
	if (args[1] == NULL)
	{
		error_message = "cd: missing args\n";
		// 2 - STDERR_FILENO (file descriptor for standard error output)
		write(STDERR_FILENO, error_message, ft_strlen(error_message));
		return ;
	}
	// changes the current working dir; if it fails, it prints the error message
	if (chdir(args[1]) != 0)
		perror("cd"); // error reporting
}
