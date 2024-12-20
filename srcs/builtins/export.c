/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:00:30 by tbolsako          #+#    #+#             */
/*   Updated: 2024/12/20 18:37:01 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to list environment variables
void	builtin_export(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		// write each env variable to standard output
		write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
