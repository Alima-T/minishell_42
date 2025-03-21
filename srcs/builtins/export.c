/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:00:30 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:57:31 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sort_env_vars(char **env_vars, int count)
{
	int		i;
	int		j;
	char	*temp;
	int		swapped;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		swapped = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_vars[j], env_vars[j + 1]) > 0)
			{
				temp = env_vars[j];
				env_vars[j] = env_vars[j + 1];
				env_vars[j + 1] = temp;
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}

static char	**build_env_array(t_env *env_dup, int count)
{
	char	**sorted_env;
	int		i;
	t_env	*tmp;

	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return (NULL);
	i = 0;
	tmp = env_dup;
	while (tmp && i < count)
	{
		sorted_env[i] = format_env_var(tmp);
		if (!sorted_env[i])
		{
			while (--i >= 0)
				free(sorted_env[i]);
			free(sorted_env);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	sorted_env[i] = NULL;
	return (sorted_env);
}

static void	list_env_vars(t_env *env_dup)
{
	int		count;
	char	**sorted_env;

	count = count_env_vars(env_dup);
	sorted_env = build_env_array(env_dup, count);
	if (!sorted_env)
		return ;
	sort_env_vars(sorted_env, count);
	print_sorted_env(sorted_env, count);
}

static int	add_or_upd_env_var(t_env **env_dup, char *arg)
{
	char	*pos;
	char	*arg_copy;
	int		result;

	arg_copy = ft_strdup(arg);
	if (!arg_copy)
		return (1);
	pos = ft_strstr(arg_copy, "+=");
	if (pos)
		result = process_append(env_dup, arg_copy, pos, arg);
	else
	{
		pos = ft_strchr(arg_copy, '=');
		if (pos)
			result = process_assignment(env_dup, arg_copy, pos, arg);
		else
			result = process_no_value(env_dup, arg_copy, arg);
	}
	free(arg_copy);
	return (result);
}

int	builtin_export(int ac, char *av[], t_env *env_dup)
{
	int	i;
	int	exit_code;

	if (ac == 1)
	{
		list_env_vars(env_dup);
		return (0);
	}
	exit_code = 0;
	i = 1;
	while (i < ac)
	{
		if (add_or_upd_env_var(&env_dup, av[i]) != 0)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
