/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:55:55 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:56:07 by tbolsako         ###   ########.fr       */
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
			ft_putstr_fd(BEGIN "msh-1.0$ " CLOSE, STDERR_FILENO);
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
