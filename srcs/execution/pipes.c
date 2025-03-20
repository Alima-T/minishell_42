/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:55:55 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 21:20:20 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Creates pipes for all commands in a pipeline
 * @param cmds Command list
 * @return 0 on success, 1 on error
 */
int	create_pipes(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp && tmp->next)
	{
		if (pipe(tmp->pipe_fd) < 0)
		{
			ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
			ft_putendl_fd("pipe: Resource temporarily unavailable",
				STDERR_FILENO);
			*get_exit_status() = 1;
			return (1);
		}
		tmp->out = tmp->pipe_fd[1];
		tmp->next->inp = tmp->pipe_fd[0];
		tmp = tmp->next;
	}
	return (0);
}

/**
 * Safely closes all pipe file descriptors in a command list
 * @param cmds Command list
 */
void	close_all_pipes(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->pipe_fd[0] > 2 && tmp->inp != tmp->pipe_fd[0])
		{
			close(tmp->pipe_fd[0]);
			tmp->pipe_fd[0] = -1;
		}
		if (tmp->pipe_fd[1] > 2 && tmp->out != tmp->pipe_fd[1])
		{
			close(tmp->pipe_fd[1]);
			tmp->pipe_fd[1] = -1;
		}
		tmp = tmp->next;
	}
}

void	close_unused_pipes(t_cmd *cmds, t_cmd *current)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp != current)
		{
			if (tmp->pipe_fd[0] > 0 && tmp->pipe_fd[0] != current->inp)
				close(tmp->pipe_fd[0]);
			if (tmp->pipe_fd[1] > 0 && tmp->pipe_fd[1] != current->out)
				close(tmp->pipe_fd[1]);
		}
		tmp = tmp->next;
	}
}

void	close_cmd_output_pipe(t_cmd *cmd)
{
	if (cmd->pipe_fd[1] > 0)
	{
		close(cmd->pipe_fd[1]);
		cmd->pipe_fd[1] = 0;
	}
}
