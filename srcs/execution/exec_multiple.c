/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:37:42 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 19:49:28 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	execute_child_process(t_cmd *cmd, t_shell *mini)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_unused_pipes(mini->cmds, cmd);
	if (help_setup_redirections(cmd) != 0)
	{
		free_shell_mem_enhanced(mini);
		env_destroy(&mini->env_dup);
		free(mini);
		exit(1);
	}
	if (is_builtin(cmd->cmd[0], mini->builtin_cmds))
	{
		status = execute_builtin(cmd, mini);
		free_shell_mem_enhanced(mini);
		env_destroy(&mini->env_dup);
		free(mini);
		exit(status);
	}
	else
		execute_external_cmd(cmd, mini);
}

static int	wait_for_processes(t_cmd *cmds)
{
	t_cmd	*cmd;
	int		status;
	int		last_status;

	cmd = cmds;
	last_status = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cleanup_cmd(cmd);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		cmd = cmd->next;
	}
	*get_exit_status() = last_status;
	return (last_status);
}

static int	fork_and_execute(t_cmd *cmd, t_shell *mini)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
		execute_child_process(cmd, mini);
	else if (cmd->pid < 0)
	{
		perror("fork");
		return (1);
	}
	close_cmd_output_pipe(cmd);
	return (0);
}

static int	create_processes(t_shell *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds;
	while (cmd)
	{
		if (fork_and_execute(cmd, mini) != 0)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	execute_multiple_cmds(t_shell *mini)
{
	int	status;
	int	*saved_fds;

	saved_fds = save_std_fds();
	if (create_pipes(mini->cmds) != 0)
	{
		close(saved_fds[0]);
		close(saved_fds[1]);
		return (1);
	}
	if (create_processes(mini) != 0)
	{
		close_all_pipes(mini->cmds);
		close(saved_fds[0]);
		close(saved_fds[1]);
		return (1);
	}
	close_all_pipes(mini->cmds);
	status = wait_for_processes(mini->cmds);
	restore_std_fds(saved_fds);
	return (status);
}
