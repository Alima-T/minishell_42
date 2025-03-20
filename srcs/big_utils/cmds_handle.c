/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:45:15 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 12:20:50 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
redir_del_node: Deletes a redirection node, frees its memory, and sets pointers
to NULL.
redir_destroy: Destroys the redirection list by deleting each node and setting
the list pointer to NULL.
cmd_del_node: Deletes a command node, frees its memory, and sets pointers to
NULL.
cmdlst_destroy: Destroys the command list by deleting each node and setting the
list pointer to NULL.
redir_del_node: Удаляет узел редиректа и освобождает память.
redir_destroy: Уничтожает весь список редиректов.
cmd_del_node: Удаляет узел команды и освобождает память.
cmdlst_destroy: Уничтожает весь список команд.
*/
/**
 * Deletes a single redirection node and frees its memory.
 * Frees the dynamically allocated type and name strings,
 * and after each delation set ptr to NULL.
 * Finaly frees node itself and sets ptr to NULL
 * @param rdrnode A pointer to the redirection node to delete.
 */
void	redir_del_node(t_redir *rdrnode)
{
	if (!rdrnode)
		return ;
	free(rdrnode->type);
	rdrnode->type = NULL;
	free(rdrnode->name);
	rdrnode->name = NULL;
	free(rdrnode);
	rdrnode = NULL;
}

/**
 * Destroys the entire redirection list and frees all allocated memory.
 * @param rdrlist A double ptr to the head of the redirection list.
 */
void	redir_destroy(t_redir **rdrlist)
{
	t_redir	*temp;

	if (!rdrlist)
		return ;
	while (*rdrlist)
	{
		temp = (*rdrlist)->next;
		redir_del_node(*rdrlist);
		*rdrlist = temp;
	}
	*rdrlist = NULL;
}

/**
 * Deletes a single command node and frees its memory.
 * @param cmdnode A pointer to the command node to delete.
 */
void	cmd_del_node(t_cmd *cmdnode)
{
	t_redir	*temp;
	int		i;

	i = 0;
	if (!cmdnode)
		return ;
	while (cmdnode->cmd[i])
	{
		if (cmdnode->cmd == NULL)
			break ;
		free(cmdnode->cmd[i]);
		cmdnode->cmd[i] = NULL;
		i++;
	}
	free(cmdnode->cmd);
	cmdnode->cmd = NULL;
	temp = (t_redir *)cmdnode->redir;
	redir_destroy(&temp);
	free(cmdnode);
	cmdnode = NULL;
}

/**
 * Destroys the entire command list and frees all allocated memory.
 * @param cmd_list A double ptr to the head of the command list.
 */
void	cmdlst_destroy(t_cmd **list)
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
