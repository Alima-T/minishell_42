/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 15:55:06 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*cmds_processing(t_shell *mini)
{
	t_arg	*tmp;
	t_arg	*cmd_begin;

	if (mini->args == NULL)
		return (NULL);
	tmp = mini->args;
	cmd_begin = tmp;
	if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		tmp = tmp->next;
	while (tmp)
	{
		if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		{
			add_cmd_lst_end(&mini->cmds, create_cmds_list(cmd_begin));
			cmd_begin = tmp->next;
		}
		tmp = tmp->next;
	}
	add_cmd_lst_end(&mini->cmds, create_cmds_list(cmd_begin));
	return (mini->cmds);
}