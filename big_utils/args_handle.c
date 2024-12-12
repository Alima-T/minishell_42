/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:39:49 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/12 19:51:35 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// Function to add a new node to the end of the list
void	add_arg_to_end(t_arg **list, t_arg *new)
{
	t_arg	*last;

	if (!list || !new) // exit for null pointers
		exit(EXIT_FAILURE); 
	if (*list) 
	{
		last = *list; // Start at the head of the list
		while (last->next) // Traverse to the last node
			last = last->next;
		last->next = new; // Link the new node at the end
	}
	else
		*list = new; // If the list is empty, set the new node as the head
}
// Function to create a new argument node
t_arg	*new_arg(char *arg_str, t_shell *mini) 
{
	t_arg	*node;

	(void)mini; // Ignore the mini parameter for now
	node = (t_arg *)malloc(sizeof(t_arg)); // Allocate memory for a new node
	if (!node) // Check if memory allocation was successful
		return (NULL); // Return NULL if allocation failed
	node->arg_val = ft_strdup(arg_str); // Duplicate the argument string
	node->redir_flag = 0; // Initialize redirect flag to 0
	node->next = NULL; // Set the next pointer to NULL
	free(arg_str); // Free the original argument string
	return (node); // Return the newly created node
}

// Function to destroy the entire list
void	destroy_list(t_arg **lst) 
{
	t_arg	*tmp;

	if (!lst) // exit for null pointer 
		return ;  
	while (*lst) // While there are nodes in the list
	{
		tmp = (*lst)->next; // Store the next node
		del_one(*lst); // Delete the current node
		*lst = tmp; // Move the head pointer to the next node
	}
	*lst = NULL; // Set the head pointer to NULL to indicate the list is empty
}

// Function to delete the first node of the list
void	del_first_node(t_arg **args) 
{
	t_arg	*next;

	if (!args || !(*args)) // Check if args is NULL or the first node is NULL
		return ; 
	next = (*args)->next; // Store the next node
	free((*args)->arg_val); // Free the argument string of the current node
	(*args)->arg_val = NULL; // Set the pointer to NULL
	free((*args)); // Free the current node
	*args = next; // Move the head pointer to the next node
}

// Function to delete a specific node
void	del_one(t_arg *lst) 
{
	if (!lst) //  and exit if node is null 
		return ; 
	free(lst->arg_val); // Free the argument string
	lst->arg_val = NULL; // Set the pointer to NULL
	free(lst); // Free the node itself
	lst = NULL; // Set the pointer to NULL locally (!! this won't affect the caller)
}

