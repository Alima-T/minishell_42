/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:17:08 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 14:58:55 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Executes a single command.
 * @param cmd Command structure
 * @param mini Shell structure
 * @return 0 on success, error code otherwise
 */
static int	execute_single_cmd(t_cmd *cmd, t_shell *mini)
{
	int	status;
	int	saved_stdout;
	int	saved_stdin;
	int	result;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (!cmd->fork && is_builtin(cmd->cmd[0], mini->builtin_cmds))
	{
		if (setup_redirections(cmd) != 0)
		{
			*get_exit_status() = 1;
			close(saved_stdout);
			close(saved_stdin);
			return (1);
		}
		result = execute_builtin(cmd, mini);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		return (result);
	}
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		cmd->fork = 1;
		close(saved_stdout);
		close(saved_stdin);
		if (setup_redirections(cmd) != 0)
			exit(1);
		if (is_builtin(cmd->cmd[0], mini->builtin_cmds))
			exit(execute_builtin(cmd, mini));
		else
			execute_external_cmd(cmd, mini);
	}
	else if (cmd->pid < 0)
	{
		ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
		ft_putendl_fd("fork: Resource temporarily unavailable", STDERR_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		return (1);
	}
	waitpid(cmd->pid, &status, 0);
	cleanup_cmd(cmd);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	if (WIFEXITED(status))
		*get_exit_status() = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*get_exit_status() = 128 + WTERMSIG(status);
	return (0);
}

/**
 * Executes a pipeline of commands.
 * @param mini Shell structure
 * @return Status of the last command
 */
static int	execute_multiple_cmds(t_shell *mini)
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

/**
 * Main command execution function that handles built-ins, signaks,
	and pipelines
 * @param mini Shell structure conatining commands and environment
 */
void	execute_cmd(t_shell *mini)
{
	t_cmd			*cmd;

	mini->builtin_cmds = init_builtin_cmds();
	if (!mini->builtin_cmds)
	{
		ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
		ft_putendl_fd("failed to initialize built-in commands", STDERR_FILENO);
		*get_exit_status() = 1;
		return ;
	}
	cmd = mini->cmds;
	while (cmd)
	{
		if (set_heredoc(cmd) != 0)
		{
			return ;
		}
		cmd = cmd->next;
	}
	if (mini->cmds && mini->cmds->next)
		execute_multiple_cmds(mini);
	else
	{
		if (mini->cmds->inp == 0)
			mini->cmds->inp = STDIN_FILENO;
		if (mini->cmds->out == 0 || mini->cmds->out == 1)
			mini->cmds->out = STDOUT_FILENO;
		execute_single_cmd(mini->cmds, mini);
	}
	free_builtin_cmds(mini->builtin_cmds);
	mini->builtin_cmds = NULL;
}
