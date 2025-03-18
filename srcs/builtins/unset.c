/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:05:23 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/18 15:31:13 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Finds an environment variable node by name
 *
 * Traverses the environment list to find a variable with the given name.
 *
 * @param env_dup Environment list to search in
 * @param name Name of the variable to find
 * @return t_env* Pointer to the found node, or NULL if not found
 */
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

/**
 * @brief Deletes an environment variable node
 *
 * Removes a node from the environment list and frees its memory.
 *
 * @param env_dup Pointer to the environment list
 * @param node Node to delete
 */
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

/**
 * @brief Removes an environment variable from the list
 *
 * Finds a variable by name and removes it from the environment list.
 *
 * @param env_dup Pointer to the environment list
 * @param name Name of the variable to remove
 * @return int 0 on success, 1 if variable not found
 */
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

/**
 * @brief Processes a single unset argument
 *
 * Validates that the variable name follows shell naming conventions
 * and attempts to remove it from the environment. Appropriate error
 * messages are displayed for invalid names or removal failures.
 *
 * @param env Pointer to the environment list
 * @param varname Name of the variable to unset
 * @return int 0 on successful removal, 1 if invalid name or removal failed
 */
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
	{
		ft_putstr_fd("unset: `", STDERR_FILENO);
		perror(varname);
		return (1);
	}
	return (0);
}

/**
 * @brief Implements the built-in unset command
 *
 * Removes one or more variables from the environment.
 *
 * @param ac Argument count
 * @param av Argument vector
 * @param env Pointer to the environment list
 * @return int 0 on success, 1 if any error occurred
 */
int	builtin_unset(int ac, char *av[], t_env **env)
{
	int	i;
	int	exit_code;

	if (ac < 2)
	{
		ft_putendl_fd("unset: missing argument", STDERR_FILENO);
		return (1);
	}
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
