/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:35:35 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 13:04:02 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
Summary of Functions:
1. copy_value: duplicates the value part of an environment variable string
(in the format KEY=VALUE). 
Returns the duplicated value or NULL if no value exists.
2. copy_key: duplicates the key part of an environment variable string.
Returns the duplicated key.
3. new_env: creates a new environment variable node. It allocates memory for
the node, duplicates the entire environment variable string, extracts the key
and value, and initializes the node's fields.
4. append_env: adds a new environment variable node to the end of a linked
list. It checks if the list is empty and either sets the new node as the head
or traverses to the end of the list and links the new node there.
5. copy_envp: copies the environment variables from an array into a linked
list. It iterates through the array, creating new nodes for each environment
variable and adding them to the linked list.
This code is part of a system for managing environment variables in a
shell-like environment, allowing for the storage and retrieval of key-value
pairs representing environment settings. It ensures proper memory management
and linked list operations for the environment variables.
 * Duplicates the value part of an environment variable string.
 * The input string is expected to be in the format "KEY=VALUE".
 * @param env_part The environment variable string to process.
 * @return A pointer to the duplicated value string, or NULL if no value exists.
 */
char	*copy_value(char *env_part)
{
	int		i;
	char	*valdup;

	i = 0;
	while (env_part[i] != '=' && env_part[i] != '\0')
		i++;
	if (env_part[i] == '\0')
		valdup = NULL;
	else
		valdup = ft_strdup(&env_part[i + 1]);
	return (valdup);
}

/**
 * Duplicates the key part of an environment variable string.
 * The input string is expected to be in the format "KEY=VALUE".
 * @param env_part The environment variable string to process.
 * @return A pointer to the duplicated key string.
 */
char	*copy_key(char *env_part)
{
	int		i;
	char	*keydup;

	i = 0;
	while (env_part[i] != '=' && env_part[i] != '\0')
		i++;
	keydup = ft_substr(env_part, 0, i);
	return (keydup);
}

/**
 * Creates a new environment variable node.
 * Allocates memory for the node and initializes its fields.
 * @param env_str The environment variable string to process.
 * t_env	*node; - Pointer to the new environment variable node
 * If the key is "OLDPWD", set the value to NULL; otherwise, copy the value
 * @return A pointer to the newly created environment variable node.
 */
t_env	*new_env(char *env_str)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->line = ft_strdup(env_str);
	node->key = copy_key(env_str);
	if (ft_strcmp(node->key, "OLDPWD") == 0)
		node->val = NULL;
	else
		node->val = copy_value(env_str);
	node->next = NULL;
	return (node);
}

/**
 * Adds a new environment variable node to the end of the linked list.
 * @param list A double pointer to the head of the environment variable list.
 * @param new A pointer to the new environment variable node to be added.
 */
void	append_env(t_env **list, t_env *new)
{
	t_env	*last;

	if (!list || !new)
		exit(EXIT_FAILURE);
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}

/**
 * Copies the environment variables from the provided array into a linked list.
 * @param envp The array of environment variable strings.
 * t_env	*envp_copy; // Pointer to the head of the new linked list
 * @return A pointer to the head of the linked list of environment variables.
 */
t_env	*copy_envp(char **envp)
{
	t_env	*envp_copy;
	int		i;

	i = 0;
	envp_copy = NULL;
	while (envp[i])
	{
		append_env(&envp_copy, new_env(envp[i]));
		i++;
	}
	return (envp_copy);
}
