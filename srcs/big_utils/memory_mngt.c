/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_mngt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:36:01 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 16:55:35 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cleanup_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->inp != STDIN_FILENO && cmd->inp > 2)
	{
		close(cmd->inp);
		cmd->inp = STDIN_FILENO;
	}
	if (cmd->out != STDOUT_FILENO && cmd->out > 2)
	{
		close(cmd->out);
		cmd->out = STDOUT_FILENO;
	}
	if (cmd->pipe_fd[0] > 2)
	{
		close(cmd->pipe_fd[0]);
		cmd->pipe_fd[0] = -1;
	}
	if (cmd->pipe_fd[1] > 2)
	{
		close(cmd->pipe_fd[1]);
		cmd->pipe_fd[1] = -1;
	}
}

void	env_destroy(t_env **list)
{
	t_env	*temp;

	if (!list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		env_del_node(*list);
		*list = temp;
	}
	*list = NULL;
}
