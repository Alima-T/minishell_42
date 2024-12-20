/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:14:03 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/20 16:48:29 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to print all env variables
int	builtin_env(char **env)
{
	int		i;
	char	**current;
	char	*equal_sign;
	char	*var;

	// check if env is NULL or empty
	if (!env || !*env)
	{
		perror("env: environment not set");
		return (1); // error if env is not set
	}
	current = env; // pointer to traverse the env variables
	while (*current)
	{
		var = *current; // get the curr env var
		equal_sign = NULL;
		i = 0;
		while (var[i] != '\0') // iterate through the characters of the var
		{
			if (var[i] == '=')
			{
				equal_sign = &var[i]; // point to the equals sign
				break ;
			}
			i++;
		}
		// if an equal sign is found, print the var
		if (equal_sign)
			printf("%.*s\n", (int)(equal_sign - var + 1), var);
		current++;
	}
	return (0);
}
