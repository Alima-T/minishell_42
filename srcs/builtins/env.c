/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:14:03 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/20 16:18:57 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to print env variables
int	builtin_env(char **env)
{
	int		i;
	char	**current;

	if (!env || !*env)
	{
		perror("env: environment not set");
		return (1);
	}
	current = env;
	while (*current)
	{
		
		write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
