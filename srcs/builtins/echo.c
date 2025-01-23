/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:34:47 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/23 17:56:08 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Prints the provided arguments to the standard output.
 * @param args
 * @return
 */
int	builtin_echo(char **args)
{
	int		i;
	int		j;
	bool	newline;

	// flag to suppress newline
	// start from the 1st arg
	i = 1;
	newline = false;
	// check for -n flags
	while (args[i] != NULL)
	{
		if (args[i][0] == '-' && ft_strcmp(args[i], "-n") == 0)
		{
			// set flag to suppress newline
			newline = true;
		}
		else if (args[i][0] == '-' && args[i][1] == 'n')
		{
			// checks if the arg starts with -n and is followed by only 'n's
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				// all characters after -n are 'n'
				newline = true;
			}
			else
			{
				// other characters present, do not suppress newline
				newline = false;
				// stop if there are other characters
				break ;
			}
		}
		else
		{
			// stop if we encounter a non-flag arg
			break ;
		}
		i++;
	}
	// iterates through the args and prints each one, adding a space
	// between them
	while (args[i] != NULL)
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
		if (args[i] != NULL)
		{
			// print space between args
			write(STDOUT_FILENO, " ", 1);
		}
	}
	// if the '-n' isn't used, it prints a newline at the end
	if (!newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
