/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:14:03 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/06 15:22:49 by tbolsako         ###   ########.fr       */
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
		// error if env is not set
		return (1);
	}
	// pointer to traverse the env variables
	current = env;
	while (*current)
	{
		// get the curr env var
		var = *current;
		equal_sign = NULL;
		i = 0;
		// iterate through the characters of the var
		while (var[i] != '\0')
		{
			if (var[i] == '=')
			{
				// point to the equals sign
				equal_sign = &var[i];
				break ;
			}
			i++;
		}
		// if an equal sign is found, print the var
		if (equal_sign)
			printf("%s\n", var);
		current++;
	}
	return (0);
}
