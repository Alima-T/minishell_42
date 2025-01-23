/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:55:59 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/23 18:07:59 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Checks if a variable name is valid.
 * @param name
 * @return
 */
int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || !isalpha(name[0]))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Prints detailed error messages.
 * @param prefix
 * @param arg
 * @param suffix
 */
void	ft_perror(const char *prefix, const char *arg, const char *suffix)
{
	if (prefix)
		write(STDERR_FILENO, prefix, ft_strlen(prefix));
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	if (suffix)
		write(STDERR_FILENO, suffix, ft_strlen(suffix));
	write(STDERR_FILENO, "\n", 1);
}
