/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:45:15 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:20:47 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redir_del_node(t_redir *rdrnode)
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

static void	redir_destroy(t_redir **rdrlist)
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

static void	cmd_del_node(t_cmd *cmdnode)
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
