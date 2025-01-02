/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:45:15 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/02 14:53:27 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// int	count_cmd_nodes(t_cmd *cmds)
// {
// 	int	count;
	
// 	count = 0;
// 	if(!cmds)
// 		return (0);
// 	while (cmds)
// 	{
// 		cmds = cmds->next;
// 		count++;
// 	}
// 	return (count);
// }

/**
 * Deletes a single command node and frees its memory.
 * @param cmd_node A pointer to the command node to delete.
 */

/**
 * Deletes a single redirection node and frees its memory.
 * Frees the dynamically allocated type and name strings,
 * and after each delation set ptr to NULL. 
 * Finaly frees node itself and sets ptr to NULL
 * @param redir_node A pointer to the redirection node to delete.
 */
void	del_redir_node(t_redir *redir_node)
{
	if (!redir_node)
		return;
	free(redir_node->type); // Free type string
	redir_node->type = NULL; // Set ptr to NULL
	free(redir_node->name); 
	redir_node->name = NULL; 
	free(redir_node); // Free the node itself
	redir_node = NULL; // Set ptr to NULL (note: does not affect caller)
}

/**
 * Destroys the entire redirection list and frees all allocated memory.
 * @param redir_list A double ptr to the head of the redirection list.
 */
void	redir_destroy(t_redir **redir_list)
{
	t_redir	*tmp; // Temp ptr to hold the next node

	if (!redir_list)
		return;
	while (*redir_list)
	{
		tmp = (*redir_list)->next; // Store the next node
		del_redir_node(*redir_list); // Delete the current node
		*redir_list = tmp;
	}
	*redir_list = NULL; // Set the head of the list to NULL (list is now empty)
}
void del_cmd_node(t_cmd *cmd_node)
{

	int		i; // Iterator for cmd array
	t_redir	*temp; // Temp pointer to the redir list

	i = 0; 
	if (!cmd_node) 
		return; 
	// Free each string in the cmd array
	while (cmd_node->cmd[i]) 
	{
		if (cmd_node->cmd == NULL) // Extra safeguard to handle NULL cmdarr
			break;
		free(cmd_node->cmd[i]); // Free current str
		cmd_node->cmd[i] = NULL; // Set ptr to NULL
		i++; 
	}
	free(cmd_node->cmd); // Free cmd_array itself
	cmd_node->cmd = NULL; // Set ptr to NULL
	temp = (t_redir *)cmd_node->redir; // Cast and store the redir list ptr
	redir_destroy(&temp); // Destroy the redir list
	free(cmd_node); // Free the cmd node itself
	cmd_node = NULL; // Set the ptr to NULL (note: does not affect caller)
}

/**
 * Destroys the entire command list and frees all allocated memory.
 * @param cmd_list A double ptr to the head of the command list.
 */
void cmd_destroy(t_cmd **list)
{
	t_cmd *temp; // Temp pointer to hold the next node
	
	if(!list)
		return ;
	while (*list)
	{
		temp = (*list)->next;// Store the next node
		cmd_lst_del_node(*list); // Delete the current node
		*list = temp;
	}
	*list = NULL;
}
