/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:34:47 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/13 16:03:25 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// prints the provided args to the standard output
void	echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	// checks if the 1st arg is '-n', which supresses the newline at the end of the output
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0; // don't print newline
		args++;
	}
	i = 1;
	// iterates through the args and prints each one, adding a space between them
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1); // print space between args
		i++;
	}
	// if the '-n' isn't used, it prints a newline at the end
	if (newline)
		write(1, "\n", 1);
}
