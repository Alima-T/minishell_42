/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:55:59 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/23 15:26:58 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

// function to check if a var name is valid
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

// function to print detailed error messages
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
