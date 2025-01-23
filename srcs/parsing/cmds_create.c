/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:23:55 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/21 13:44:01 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Finds the position of the command in the linked list of arguments.
 * Counts the number of arguments until a pipe character is found.
 * @param args A pointer to the linked list of arguments.
 * @return The position of the command or 0 if a pipe is found.
 */
int	find_cmd(t_arg *args)
{
	t_arg	*tmp;
	int		count; // Counts the number of arguments

	if (!args)
		return (0);
	tmp = args;
	count = 1;
	// Check the argument is a pipe and returnes 0,if true
	if (ft_strcmp("|", tmp->arg_val) == 0)
		return (0);
	while (tmp->next) // Traverse the linked list until the end
	{
		tmp = tmp->next;
		if (ft_strcmp(tmp->arg_val, "|") == 0) // Check if the current argument is a pipe
			return (count); // Return the count if a pipe is found
		count++; // Increment the count for each argument
	}
	return (count); 
}

/**
 * Converts a linked list of arguments into an array of strings.
 * Allocates memory for the array and duplicates each argument string.
 * @param args A pointer to the linked list of arguments.
 * @param lists_count The number of arguments to convert.
 * @return A pointer to the created array of strings
 */
char	**turn_cmd_to_array(t_arg *args, int lists_count)
{
	char	**args_array; // Pointer to the array of args
	int		i;

	i = 0;
	args_array = (char **)malloc(sizeof(char *) * (lists_count + 1));
	if (!args_array)
		return (NULL);
	// Go to the linked list and copy its elements into the array
	// Continue until the list is empty or all elements are processed
	while (args && (lists_count != 0))
	{
		args_array[i] = ft_strdup(args->arg_val);
		args = args->next;
		lists_count--;
		i++;
	}
	args_array[i] = NULL;
	return (args_array);
}

/**
 * Creates a command structure from the linked list of arguments.
 * Allocates memory for the command structure and initializes its fields.
 * @param args A pointer to the linked list of arguments.
 * int lists_count; // Number of arguments in the linked list
 * t_cmd *element; // Pointer to the command structure
 * @return A pointer to the created command structure or NULL if allocation fails.
 */
t_cmd	*create_cmds_list(t_arg *args)
{
	int lists_count;
	t_cmd *element;
	
	element = (t_cmd *) malloc(sizeof(t_cmd));
	if (!element || !args)
		return (NULL);
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