/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_mngt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:36:01 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:36:29 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Safely frees resources and closes file descriptors for a command
 * @param cmd Command structure to clean up
 */
void	cleanup_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	// close any open file descriptors
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
	// close pipe file descriptors if they're open
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

/**
 * Ensures all temporary files from heredocs are cleaned up
 */
void	cleanup_heredoc_files(void)
{
	char	*cmd;

	// remove any temporary heredoc files that might have been left behind
	cmd = "rm -f /tmp/.heredoc_*";
	system(cmd);
}
