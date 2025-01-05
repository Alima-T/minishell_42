/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:05:23 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/05 16:55:03 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to remove an env var from a local env list
static int	remove_env_var(char **env, const char *name)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(name);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			// free the memory of the var to be removed
			free(env[i]);
			// shift the remaining env vars down
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	// var not found
	return (1);
}

// function to remove an env variable
int	builtin_unset(int ac, char *av[], char ***env)
{
	const char	*error_message;
	int			i;

	if (ac < 2)
	{
		error_message = "unset: missing argument\n";
		write(STDERR_FILENO, error_message, ft_strlen(error_message));
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (is_valid_var_name(av[i]))
		{
			if (remove_env_var(*env, av[i]) != 0)
			{
				perror("unset");
				return (1);
			}
		}
		else
		{
			write(STDERR_FILENO, "unset: not a valid identifier\n", 30);
			return (1);
		}
		i++;
	}
	return (0);
}
