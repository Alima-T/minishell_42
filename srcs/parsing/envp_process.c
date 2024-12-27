/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:35:35 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 15:18:32 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h" // Includes the header file for the minishell project

/**
Summary of Functions:
1. copy_value:
This function duplicates the value part of an environment variable string (in the format KEY=VALUE). It returns the duplicated value or NULL if no value exists.
copy_key:
This function duplicates the key part of an environment variable string. It returns the duplicated key.
3. envl_lstnew:
This function creates a new environment variable node. It allocates memory for the node, duplicates the entire environment variable string, extracts the key and value, and initializes the node's fields.
4. envl_lstadd_back:
This function adds a new environment variable node to the end of a linked list. It checks if the list is empty and either sets the new node as the head or traverses to the end of the list and links the new node there.
copy_envp:
This function copies the environment variables from an array into a linked list. It iterates through the array, creating new nodes for each environment variable and adding them to the linked list.
This code is part of a system for managing environment variables in a shell-like environment, allowing for the storage and retrieval of key-value pairs representing environment settings. It ensures proper memory management and linked list operations for the environment variables.
 * Duplicates the value part of an environment variable string.
 * The input string is expected to be in the format "KEY=VALUE".
 *
 * @param env_part The environment variable string to process.
 * @return A pointer to the duplicated value string, or NULL if no value exists.
 */
char	*copy_value(char *env_part)
{
	int		it; // Index to traverse the string
	char	*val; // Pointer to hold the duplicated value

	it = 0; // Initialize index
	// Traverse the string until '=' or end of string
	while (env_part[it] != '=' && env_part[it] != '\0')
		it++;
	if (env_part[it] == '\0') // If no '=' found, there is no value
		val = NULL; // Set value to NULL
	else
		val = ft_strdup(&env_part[it + 1]); // Duplicate the value part (after '=')
	return (val); // Return the duplicated value
}

/**
 * Duplicates the key part of an environment variable string.
 * The input string is expected to be in the format "KEY=VALUE".
 *
 * @param env_part The environment variable string to process.
 * @return A pointer to the duplicated key string.
 */
char	*copy_key(char *env_part)
{
	int		i; // Index to traverse the string
	char	*key; // Pointer to hold the duplicated key

	i = 0; // Initialize index
	// Traverse the string until '=' or end of string
	while (env_part[i] != '=' && env_part[i] != '\0')
		i++;
	key = ft_substr(env_part, 0, i); // Duplicate the key part (before '=')
	return (key); // Return the duplicated key
}

/**
 * Creates a new environment variable node.
 * Allocates memory for the node and initializes its fields.
 *
 * @param env_str The environment variable string to process.
 * @return A pointer to the newly created environment variable node.
 */
t_env	*envl_lstnew(char *env_str)
{
	t_env	*element; // Pointer to the new environment variable node

	element = (t_env *)malloc(sizeof(t_env)); // Allocate memory for the new node
	if (!element) // Check if memory allocation failed
		return (NULL); // Return NULL if allocation fails
	element->line = ft_strdup(env_str); // Duplicate the entire environment variable string
	element->key = copy_key(env_str); // Extract and duplicate the key
	// If the key is "OLDPWD", set the value to NULL; otherwise, copy the value
	if (ft_strcmp(element->key, "OLDPWD") == 0)
		element->value = NULL; // Set value to NULL for "OLDPWD"
	else
		element->value = copy_value(env_str); // Copy the value part
	element->next = NULL; // Initialize the next pointer to NULL (end of the list)
	return (element); // Return the newly created node
}

/**
 * Adds a new environment variable node to the end of the linked list.
 *
 * @param list A double pointer to the head of the environment variable list.
 * @param new A pointer to the new environment variable node to be added.
 */
void	envl_lstadd_back(t_env **list, t_env *new)
{
	t_env	*last; // Pointer to traverse the list

	if (!list || !new) // Check if the list or new node is NULL
		exit(EXIT_FAILURE); // Exit if either is NULL
	if (*list) // If the list is not empty
	{
		last = *list; // Start from the head of the list
		while (last->next) // Traverse to the end of the list
			last = last->next; // Move to the next node
		last->next = new; // Link the new node at the end
	}
	else
		*list = new; // If the list is empty, set the new node as the head
}

/**
 * Copies the environment variables from the provided array into a linked list.
 *
 * @param envp The array of environment variable strings.
 * @return A pointer to the head of the linked list of environment variables.
 */
t_env	*copy_envp(char **envp)
{
	t_env	*envp_copy; // Pointer to the head of the new linked list
	int		it; // Index to traverse the environment variable array

	it = 0; // Initialize index
	envp_copy = NULL; // Initialize the linked list to NULL
	// Loop through the environment variable array
	while (envp[it])
	{
		envl_lstadd_back(&envp_copy, envl_lstnew(envp[it])); // Add each environment variable to the list
		it++; // Move to the next environment variable
	}
	return (envp_copy); // Return the head of the linked list
}