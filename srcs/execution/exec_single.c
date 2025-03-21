/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:19:29 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 19:50:24 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	save_and_restore_io(int *saved_out, int *saved_in, int restore)
{
	if (!restore)
	{
		*saved_out = dup(STDOUT_FILENO);
		*saved_in = dup(STDIN_FILENO);
	}
	else
	{
		dup2(*saved_out, STDOUT_FILENO);
		dup2(*saved_in, STDIN_FILENO);
		close(*saved_out);
		close(*saved_in);
	}
}

static int	handle_builtin_no_fork(t_cmd *cmd, t_shell *mini, int *saved_out,
		int *saved_in)
{
	int	result;

	if (help_setup_redirections(cmd) != 0)
	{
		*get_exit_status() = 1;
		save_and_restore_io(saved_out, saved_in, 1);
		return (1);
	}
	result = execute_builtin(cmd, mini);
	save_and_restore_io(saved_out, saved_in, 1);
	return (result);
}

static void	handle_child_process(t_cmd *cmd, t_shell *mini)
{
	int	status;

	cmd->fork = 1;
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

static int	handle_fork_error(int *saved_out, int *saved_in)
{
	ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
	ft_putendl_fd("fork: Resource temporarily unavailable", STDERR_FILENO);
	close(*saved_out);
	close(*saved_in);
	return (1);
}

int	execute_single_cmd(t_cmd *cmd, t_shell *mini)
{
	int	status;
	int	saved_stdout;
	int	saved_stdin;

	save_and_restore_io(&saved_stdout, &saved_stdin, 0);
	if (!cmd->fork && is_builtin(cmd->cmd[0], mini->builtin_cmds))
		return (handle_builtin_no_fork(cmd, mini, &saved_stdout, &saved_stdin));
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		close(saved_stdout);
		close(saved_stdin);
		handle_child_process(cmd, mini);
	}
	else if (cmd->pid < 0)
		return (handle_fork_error(&saved_stdout, &saved_stdin));
	waitpid(cmd->pid, &status, 0);
	cleanup_cmd(cmd);
	save_and_restore_io(&saved_stdout, &saved_stdin, 1);
	if (WIFEXITED(status))
		*get_exit_status() = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*get_exit_status() = 128 + WTERMSIG(status);
	return (0);
}
