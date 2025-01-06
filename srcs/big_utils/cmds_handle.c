/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:45:15 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/06 17:50:40 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
redir_del_node: Deletes a redirection node, frees its memory, and sets pointers to NULL.
redir_destroy: Destroys the redirection list by deleting each node and setting the list pointer to NULL.
cmd_del_node: Deletes a command node, frees its memory, and sets pointers to NULL.
cmd_destroy: Destroys the command list by deleting each node and setting the list pointer to NULL.
redir_del_node: Удаляет узел редиректа и освобождает память.
redir_destroy: Уничтожает весь список редиректов.
cmd_del_node: Удаляет узел команды и освобождает память.
cmd_destroy: Уничтожает весь список команд.
*/
/**
 * Deletes a single redirection node and frees its memory.
 * Frees the dynamically allocated type and name strings,
 * and after each delation set ptr to NULL. 
 * Finaly frees node itself and sets ptr to NULL
 * @param redir_node A pointer to the redirection node to delete.
 */
void	redir_del_node(t_redir *redir_node)
{
	if (!redir_node)
		return ;
	free(redir_node->type);
	redir_node->type = NULL;
	free(redir_node->name);
	redir_node->name = NULL;
	free(redir_node);
	redir_node = NULL;
}

/**
 * Destroys the entire redirection list and frees all allocated memory.
 * @param redir_list A double ptr to the head of the redirection list.
 */
void	redir_destroy(t_redir **redir_list)
{
	t_redir	*temp;	// Temp ptr to hold the next node

	if (!redir_list)
		return ;
	while (*redir_list)
	{
		temp = (*redir_list)->next;
		redir_del_node(*redir_list);
		*redir_list = temp;
	}
	*redir_list = NULL;
}

/**
 * Deletes a single command node and frees its memory.
 * @param cmd_node A pointer to the command node to delete.
 */
void	cmd_del_node(t_cmd *cmd_node)
{
	t_redir	*temp;
	int		i;

	i = 0;
	if (!cmd_node)
		return ;
	while (cmd_node->cmd[i])
	{
		if (cmd_node->cmd == NULL)
			break ;
		free(cmd_node->cmd[i]);
		cmd_node->cmd[i] = NULL;
		i++;
	}
	free(cmd_node->cmd);
	cmd_node->cmd = NULL;
	temp = (t_redir *)cmd_node->redir;
	redir_destroy(&temp);
	free(cmd_node);
	cmd_node = NULL;
}

/**
 * Destroys the entire command list and frees all allocated memory.
 * @param cmd_list A double ptr to the head of the command list.
 */
void	cmd_destroy(t_cmd **list)
{
	t_cmd	*temp;

	if (!list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		cmd_del_node(*list);
		*list = temp;
	}
	*list = NULL;
}
