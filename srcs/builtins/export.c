/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:00:30 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/06 15:19:50 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to sort env vars using bubble sort
static void	bubble_sort(char **arr, int n)
{
	int		i;
	int		j;
	char	*temp;
	int		swapped;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		swapped = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}

// function to list env vars
static void	list_env_vars(char **env)
{
	int		i;
	char	**sorted_env;

	i = 0;
	while (env[i] != NULL)
		i++;
	sorted_env = malloc(sizeof(char *) * (i + 1));
	if (!sorted_env)
		return ;
	i = 0;
	while (env[i] != NULL)
	{
		sorted_env[i] = env[i];
		i++;
	}
	sorted_env[i] = NULL;
	bubble_sort(sorted_env, i);
	i = 0;
	while (sorted_env[i] != NULL)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, sorted_env[i], ft_strlen(sorted_env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	free(sorted_env);
}

// function to add or update an env var
static int	add_or_upd_env_var(char *arg)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		// split the arg into name and value
		*equal_sign = '\0';
		name = arg;
		value = equal_sign + 1;
		if (is_valid_var_name(name))
		{
			if (setenv(name, value, 1) != 0)
			{
				perror("export: failed to set env var");
				return (1);
			}
		}
		else
		{
			write(STDERR_FILENO, "export: not a valid identifier\n", 31);
			return (1);
		}
	}
	else
	{
		// no '=' found, set the var with an empty value
		if (is_valid_var_name(arg))
		{
			if (setenv(arg, "", 1) != 0)
			{
				perror("export: failed to set env var");
				return (1);
			}
		}
		else
		{
			write(STDERR_FILENO, "export: not a valid identifier\n", 31);
			return (1);
		}
	}
	return (0);
}

// function to list environment variables
int	builtin_export(int ac, char *av[], char **env)
{
	int	i;

	if (ac == 1)
	{
		// no args, list all env vars
		list_env_vars(env);
		return (0);
	}
	else
	{
		// process each arg
		i = 1;
		while (i < ac)
		{
			if (add_or_upd_env_var(av[i]) != 0)
				return (1);
			i++;
		}
	}
	return (0);
}
