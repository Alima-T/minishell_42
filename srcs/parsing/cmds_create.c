/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:23:55 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/02 17:21:51 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
Summary of Functions:
find_cmd:
This function traverses a linked list of arguments to find the position of the command and counts the number of arguments until a pipe character (|) is encountered. It returns the count of arguments or 0 if a pipe is found at the start.
turn_cmd_to_array:
This function converts a linked list of arguments into an array of strings. It allocates memory for the array, duplicates each argument string, and returns the array. The last element of the array is set to NULL.
3. create_cmds_list:
This function creates a command structure from the linked list of arguments. It allocates memory for the command structure, processes redirections, counts the arguments, converts them to an array, and initializes various fields (like input/output file descriptors and pipe ends).
4. add_cmd_lst_end:
This function adds a new command structure to the end of the command list. It checks if the list is empty and either sets the new command as the head or traverses to the end of the list and links the new command there.
This code is part of a command management system for a shell-like environment, responsible for creating and managing command structures based on user input. It handles argument parsing, command creation, and linking commands in a list for execution.
*/

/**
 * Finds the position of the command in the linked list of arguments.
 * Counts the number of arguments until a pipe character is found.
 *
 * @param args A pointer to the linked list of arguments.
 * @return The position of the command or 0 if a pipe is found.
 */
int	find_cmd(t_arg *args)
{
	t_arg	*tmp; // Temporary pointer to traverse the argument list
	int		count; // Counter for the number of arguments

	if (!args) // Check if the argument list is NULL
		return (0); // Return 0 if the list is empty
	tmp = args; // Initialize the temporary pointer to the head of the list
	count = 1; // Start counting from 1
	if (ft_strcmp("|", tmp->arg_val) == 0) // Check if the first argument is a pipe
		return (0); // Return 0 if the first argument is a pipe
	while (tmp->next) // Traverse the linked list until the end
	{
		tmp = tmp->next; // Move to the next argument
		if (ft_strcmp(tmp->arg_val, "|") == 0) // Check if the current argument is a pipe
			return (count); // Return the count if a pipe is found
		count++; // Increment the count for each argument
	}
	return (count); // Return the total count of arguments
}

/**
 * Converts a linked list of arguments into an array of strings.
 * Allocates memory for the array and duplicates each argument string.
 *
 * @param args A pointer to the linked list of arguments.
 * @param lists_count The number of arguments to convert.
 * @return A pointer to the array of strings or NULL if allocation fails.
 */
char	**turn_cmd_to_array(t_arg *args, int lists_count)
{
	char	**args_array; // Pointer to the array of strings
	int		i; // Index variable for the array

	i = 0; // Initialize the index
	args_array = (char **)malloc(sizeof(char *) * (lists_count + 1)); // Allocate memory for the array
	if (!args_array) // Check if memory allocation failed
		return (NULL); // Return NULL if allocation fails
	// Go to the linked list and copy its elements into the array
	while (args && (lists_count != 0)) // Continue until the list is empty or all elements are processed
	{
		args_array[i] = ft_strdup(args->arg_val); // Duplicate the argument string and store it in the array
		args = args->next; // Move to the next argument
		lists_count--; // Decrement the count of remaining elements
		i++; // Increment to move to the next array position
	}
	args_array[i] = NULL; // Set the last element of the array to NULL
	return (args_array); // Return the created array of strings
}

/**
 * Creates a command structure from the linked list of arguments.
 * Allocates memory for the command structure and initializes its fields.
 *
 * @param args A pointer to the linked list of arguments.
 * @return A pointer to the created command structure or NULL if allocation fails.
 */
t_cmd	*create_cmds_list(t_arg *args)
{
	int lists_count; // Number of arguments in the linked list
	t_cmd *element; // Pointer to the command structure

	element = (t_cmd *) malloc(sizeof(t_cmd)); // Allocate memory for the command structure
	if (!element || !args) // Check if allocation failed or if args is NULL
		return (NULL); // Return NULL if either condition is true
	element->redir = NULL; // Initialize the redirection field to NULL
	element->redir = (struct s_redir *) redirect_process(&args); // Process redirections and store the result
	lists_count = find_cmd(args); // Find the number of arguments in the list
	element->cmd = turn_cmd_to_array(args, lists_count); // Convert the argument list to an array
	element->inp = 0; // Initialize input file descriptor to 0 (stdin)
	element->out = 1; // Initialize output file descriptor to 1 (stdout)
	element->fork = 0; // Initialize fork flag to 0 (not forked yet)
	element->pipe_fd[0] = 0; // Initialize read end of pipe to 0
	element->pipe_fd[1] = 0; // Initialize write end of pipe to 0
	element->next = NULL; // Set the next pointer to NULL (end of the list)
	return (element); // Return the created command structure
}

/**
 * Adds a new command structure to the end of the command list.
 *
 * @param list A double pointer to the head of the command list.
 * @param new A pointer to the new command structure to be added.
 */
void	add_cmd_lst_end(t_cmd **list, t_cmd *new) 
{
	t_cmd	*last; // Pointer to traverse the command list

	if (!list || !new) // Check if the list or new command is NULL
		exit(EXIT_FAILURE); // Exit if either is NULL
	if (*list) // If the command list is not empty
	{
		last = *list; // Start from the head of the list
		while (last->next) // Traverse to the end of the list
			last = last->next; // Move to the next command
		last->next = new; // Link the new command at the end
	}
	else
		*list = new; // If the list is empty, set the new command as the head
}