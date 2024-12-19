/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:34:47 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/19 14:12:31 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// prints the provided args to the standard output
void	builtin_echo(char **args)
{
	int	newline;
	int	i;

	newline = 1; // flag to determine if a newline should be printed
				// checks if the 1st arg is '-n', which supresses the newline
				// at the end of the output 
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0; // don't print newline
		args++;
	}
	i = 1;
	// iterates through the args and prints each one,adding a space 
	// between them 
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1); // print space between args
		i++;
	}
	// if the '-n' isn't used, it prints a newline at the end
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}
