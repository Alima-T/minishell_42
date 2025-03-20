/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:37:42 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 15:38:15 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Executes a pipeline of commands.
 * @param mini Shell structure
 * @return Status of the last command
 */
int	execute_multiple_cmds(t_shell *mini)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		status;
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (create_pipes(mini->cmds) != 0)
	{
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	cmd = mini->cmds;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			tmp = mini->cmds;
			while (tmp)
			{
				if (tmp != cmd)
				{
					if (tmp->pipe_fd[0] > 0 && tmp->pipe_fd[0] != cmd->inp)
						close(tmp->pipe_fd[0]);
					if (tmp->pipe_fd[1] > 0 && tmp->pipe_fd[1] != cmd->out)
						close(tmp->pipe_fd[1]);
				}
				tmp = tmp->next;
			}
			if (setup_redirections(cmd) != 0)
				exit(1);
			if (is_builtin(cmd->cmd[0], mini->builtin_cmds))
				exit(execute_builtin(cmd, mini));
			else
				execute_external_cmd(cmd, mini);
		}
		else if (cmd->pid < 0)
		{
			perror("fork");
			close_all_pipes(mini->cmds);
			close(saved_stdin);
			close(saved_stdout);
			return (1);
		}
		if (cmd->pipe_fd[1] > 0)
		{
			close(cmd->pipe_fd[1]);
			cmd->pipe_fd[1] = 0;
		}
		cmd = cmd->next;
	}
	cmd = mini->cmds;
	while (cmd)
	{
		if (cmd->pipe_fd[0] > 0)
		{
			close(cmd->pipe_fd[0]);
			cmd->pipe_fd[0] = 0;
		}
		if (cmd->pipe_fd[1] > 0)
		{
			close(cmd->pipe_fd[1]);
			cmd->pipe_fd[1] = 0;
		}
		cmd = cmd->next;
	}
	cmd = mini->cmds;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cleanup_cmd(cmd);
		if (WIFEXITED(status))
			*get_exit_status() = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*get_exit_status() = 128 + WTERMSIG(status);
		cmd = cmd->next;
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (*get_exit_status());
}
