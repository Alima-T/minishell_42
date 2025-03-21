/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:05:23 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:57:51 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_env	*find_env_node(t_env *env_dup, const char *name)
{
	while (env_dup)
	{
		if (!ft_strcmp(env_dup->key, name))
			return (env_dup);
		env_dup = env_dup->next;
	}
	return (NULL);
}

static void	del_node(t_env **env_dup, t_env *node)
{
	t_env	*current;
	t_env	*prev;

	current = *env_dup;
	prev = NULL;
	while (current)
	{
		if (current == node)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_dup = current->next;
			free(current->line);
			free(current->key);
			free(current->val);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static int	remove_env_var(t_env **env_dup, const char *name)
{
	t_env	*node;

	node = find_env_node(*env_dup, name);
	if (node)
	{
		del_node(env_dup, node);
		return (0);
	}
	return (1);
}

static int	process_unset_arg(t_env **env, char *varname)
{
	if (!validate_var_name(varname))
	{
		ft_putstr_fd(BEGIN "minishell: "CLOSE "unset: `", STDERR_FILENO);
		ft_putstr_fd(varname, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	if (remove_env_var(env, varname) != 0)
		return (0);
	return (0);
}

int	builtin_unset(int ac, char *av[], t_env **env)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	i = 1;
	while (i < ac)
	{
		if (process_unset_arg(env, av[i]) != 0)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
