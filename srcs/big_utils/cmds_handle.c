/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:45:15 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/02 14:15:57 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//TODO
void cmd_lst_del_node(t_cmd *list)
{
	
}

void cmd_destroy(t_cmd **list)
{
	t_cmd *temp;
	
	if(list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		cmd_lst_del_node(*list);
		*list = temp;
	}
	*list = NULL;
}
