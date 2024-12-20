/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:34:47 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/20 15:48:28 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// prints the provided args to the standard output
int	builtin_echo(char **args)
{
	int	i;
	int	j;
	bool newline; // flag to suppress newline

	i = 1; // start from the 1st arg
	newline = false;
	// check for -n flags
	while (args[i] != NULL)
	{
		if (args[i][0] == '-' && ft_strcmp(args[i], "-n") == 0)
			newline = true; // set flag to suppress newline
		else if (args[i][0] == '-' && args[i][1] == 'n')
		{
			// checks if the arg starts with -n and is followed by only 'n's
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
				newline = true; // all characters after -n are 'n'
			else
			{
				newline = false; // other characters present,
									// do not suppress newline
				break ; // stop if there are other characters
			}
		}
		else
			break ; // stop if we encounter a non-flag arg
		i++;
	}
	// iterates through the args and prints each one, adding a space
	// between them
	while (args[i] != NULL)
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
		if (args[i] != NULL)
			write(STDOUT_FILENO, " ", 1); // print space between args
	}
	// if the '-n' isn't used, it prints a newline at the end
	if (!newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
