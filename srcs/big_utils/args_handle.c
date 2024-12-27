/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:39:49 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 13:45:46 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/** 
Summary of Functions:
new_arg: Creates a new argument node, duplicates the argument string, and initializes the node.
add_arg_end: Adds a new node to the end of the linked list of argument nodes.
del_first_node: Deletes the first node in the list and frees its memory.
del_one: Deletes a specific node and frees its memory.
list_destroy: Deletes all nodes in the list, freeing all allocated memory.
This code is part of a linked list implementation for managing command-line arguments in a shell-like environment.

 * Creates a new argument node with the given argument string.
 * Allocates memory for the new node and duplicates the argument string.
 *
 * @param arg_str The argument string to be stored in the new node.
 * @param mini A pointer to the shell structure (not used in this function).
 * @return A pointer to the newly created argument node,
 *         or NULL if allocation fails.
 */

t_arg	*new_arg(char *arg_str, t_shell *mini)
{
	t_arg	*el; // Pointer to the new argument node

	(void)mini; // Ignore the mini parameter as it's not used
	el = (t_arg *)malloc(sizeof(t_arg)); // Allocate memory for the new node
	if (!el) // Check if memory allocation failed
		return (NULL); // Return NULL if allocation fails
	el->arg_val = ft_strdup(arg_str); // Duplicate the argument string
	el->redir_flag = 0; // Initialize the redirection flag to 0
	el->next = NULL; // Set the next pointer to NULL (end of the list)
	free(arg_str); // Free the original argument string
	return (el); // Return the newly created node
}

/**
 * Adds a new argument node to the end of the linked list.
 * If the list is empty, the new node becomes the head of the list.
 *
 * @param lst A double pointer to the head of the list.
 * @param new A pointer to the new argument node to be added.
 */
void	add_arg_end(t_arg **lst, t_arg *new)
{
	t_arg	*last; // Pointer to traverse the list

	if (!lst || !new) // Check if the list or new node is NULL
		exit(EXIT_FAILURE); // Exit if either is NULL
	if (*lst) // If the list is not empty
	{
		last = *lst; // Start from the head of the list
		while (last->next) // Traverse to the end of the list
			last = last->next; // Move to the next node
		last->next = new; // Link the new node at the end
	}
	else
		*lst = new; // If the list is empty, set the new node as the head
}

/**
 * Deletes the first node in the argument list.
 * Frees the memory allocated for the argument string and the node itself.
 *
 * @param args A double pointer to the head of the argument list.
 */
void	del_first_node(t_arg **args)
{
	t_arg	*next; // Pointer to the next node

	if (!args || !(*args)) // Check if the list is NULL or empty
		return; // Exit if the list is NULL or empty
	next = (*args)->next; // Store the next node
	free((*args)->arg_val); // Free the argument string of the first node
	(*args)->arg_val = NULL; // Set the argument string pointer to NULL
	free((*args)); // Free the first node
	*args = next; // Update the head to the next node
}

/**
 * Deletes a specific argument node and frees its memory.
 *
 * @param lst A pointer to the argument node to be deleted.
 */
void	del_one(t_arg *lst)
{
	if (!lst) // Check if the node is NULL
		return; // Exit if the node is NULL
	free(lst->arg_val); // Free the argument string
	lst->arg_val = NULL; // Set the argument string pointer to NULL
	free(lst); // Free the node itself
	lst = NULL; // Set the node pointer to NULL (note: this does not affect the caller)
}

/**
 * Destroys the entire argument list by deleting each node.
 * Frees all allocated memory for the argument strings and nodes.
 *
 * @param lst A double pointer to the head of the argument list.
 */
void	list_destroy(t_arg **lst)
{
	t_arg	*tmp; // Temporary pointer to hold the next node

	if (!lst) // Check if the list is NULL
		return; // Exit if the list is NULL
	while (*lst) // While there are nodes in the list
	{
		tmp = (*lst)->next; // Store the next node
		del_one(*lst); // Delete the current node
		*lst = tmp; // Move to the next node
	}
	*lst = NULL; // Set the head of the list to NULL (list is now empty)
}
