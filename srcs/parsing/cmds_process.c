/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:32:05 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	append_cmd(t_cmd **list, t_cmd *new)
{
	t_cmd	*last;

	if (!list || !new)
		exit(EXIT_FAILURE);
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}

static void	process_cmds_and_redirs(t_shell *mini)
{
	t_cmd	*cmd;
	t_redir	*rdr;
	int		i;

	cmd = mini->cmds;
	rdr = (t_redir *) mini->cmds->redir;
	while (cmd)
	{
		if (cmd->cmd)
		{
			i = 0;
			while (cmd->cmd[i])
			{
				cmd->cmd[i] = parse_special_chars(cmd->cmd[i], mini->env_dup);
				i++;
			}
		}
		while (rdr)
		{
			rdr->name = parse_special_chars(rdr->name, mini->env_dup);
			rdr = rdr->next;
		}
		cmd = cmd->next;
	}
}

t_cmd	*cmds_process(t_shell *mini)
{
	t_arg	*tmp;
	t_arg	*cmd_start;

	if (mini->args == NULL)
		return (NULL);
	tmp = mini->args;
	cmd_start = tmp;
	if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		tmp = tmp->next;
	while (tmp)
	{
		if ((ft_strcmp(tmp->arg_val, "|")) == 0)
		{
			append_cmd(&mini->cmds, create_cmds_lst(cmd_start));
			cmd_start = tmp->next;
		}
		tmp = tmp->next;
	}
	append_cmd(&mini->cmds, create_cmds_lst(cmd_start));
	process_cmds_and_redirs(mini);
	return (mini->cmds);
}
