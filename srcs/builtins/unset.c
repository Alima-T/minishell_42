/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:05:23 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/04 15:14:11 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Removes an environment variable from a local environment list.
 * @param env
 * @param name
 * @return
 */
static int	remove_env_var(char **env, const char *name)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(name);
	i = 0;
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

/**
 * Unsets an environment variable.
 * @param ac
 * @param av
 * @param env
 * @return
 */
int	builtin_unset(int ac, char *av[], char ***env)
{
	int	i;
	int	exit_code;

	if (ac < 2)
	{
		write(STDERR_FILENO, "unset: missing argument\n", 24);
		return (1);
	}
	exit_code = 0;
	i = 1;
	while (i < ac)
	{
		if (!is_valid_var_name(av[i]))
		{
			ft_perror("msh-1.0: unset: `", av[i],
				"': not a valid identifier");
			exit_code = 1;
		}
		else if (remove_env_var(*env, av[i]) != 0)
		{
			perror("unset");
			exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}
