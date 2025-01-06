/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/06 15:53:08 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Summary of the Function:
Purpose: The process_cmds function processes a linked list of arguments from a shell structure (t_shell *mini) and creates a list of commands (t_cmd) based on the presence of pipe characters (|).
Logic:
It first checks if there are any arguments. If not, it returns NULL.
It initializes pointers to traverse the argument list and to mark the beginning of each command.
It loops through the arguments, checking for pipe characters. When a pipe is found, it creates a command from the arguments collected so far and updates the starting point for the next command.
After the loop, it ensures that the last segment of arguments is also processed into a command.
Return Value: The function returns a linked list of commands created from the input arguments.
*/

t_cmd	*process_cmds(t_shell *mini)
{
	t_arg	*tmp; // Temporary pointer to traverse the linked list of arguments
	t_arg	*cmd_begin; // Pointer to mark the beginning of a command
	// Check if the argument list is empty; if so, return NULL
	if (mini->args == NULL)
		return (NULL); // Return NULL if there are no arguments
	tmp = mini->args; // Initialize the temporary pointer to the head of the argument list
	cmd_begin = tmp; // Set the command beginning pointer to the current argument
	// Check if the first argument is a pipe; if so, move to the next argument
	if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		tmp = tmp->next; // Move to the next argument if the first is a pipe
	// Loop through the argument list to process commands
	while (tmp)
	{
		// Check if the current argument is a pipe
		if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		{
			// If a pipe is found, create a command from the arguments collected so far
			add_cmd_lst_end(&mini->cmds, create_cmds_list(cmd_begin));
			cmd_begin = tmp->next; // Update the command beginning pointer to the next argument
		}
		tmp = tmp->next; // Move to the next argument in the list
	}
	// After the loop, create a command for the last segment of arguments
	add_cmd_lst_end(&mini->cmds, create_cmds_list(cmd_begin));
	return (mini->cmds); // Return the list of commands created
}