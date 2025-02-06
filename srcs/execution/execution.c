/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:17:08 by tbolsako          #+#    #+#             */
/*   Updated: 2025/02/06 18:53:30 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Handles the execution of external commands.
 * @param cmd
 * @param mini
 * @return
 */
int	execute_external_cmd(t_cmd *cmd, t_shell *mini)
{
	char	**envp;
	char	*executable;

	envp = env_list_to_array(mini->env_dup);
	if (!envp)
	{
		perror("env_list_to_array");
		exit(1);
	}
	executable = find_executable(cmd->cmd[0]);
	if (!executable)
	{
		ft_perror("minishell: ", cmd->cmd[0], ": command not found");
		free_array(envp);
		// exit 127 for command not found
		exit(127);
	}
	execve(executable, cmd->cmd, envp);
	perror("execve");
	free_array(envp);
	free(executable);
	exit(EXIT_FAILURE);
}

/**
 * Executes a built-in command.
 * @param cmd
 * @param mini
 * @return
 */
int	execute_builtin(t_cmd *cmd, t_shell *mini)
{
	int		cmd_count;
	char	**env_array;

	cmd_count = count_args(cmd->cmd);
	env_array = env_list_to_array(mini->env_dup);
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (builtin_cd(cmd_count, cmd->cmd));
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (builtin_echo(cmd->cmd));
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (builtin_env(env_array));
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (builtin_export(cmd_count, cmd->cmd, env_array));
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (builtin_unset(cmd_count, cmd->cmd, &env_array));
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
	{
		free_array(env_array);
		builtin_exit(cmd_count, cmd->cmd);
	}
	free_array(env_array);
	return (1);
}

/**
 * Executes a single command.
 * @param cmd
 * @param mini
 * @return
 */
int	execute_single_cmd_with_redir(t_cmd *cmd, t_shell *mini)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd->cmd[0], mini->builtin_cmds))
		return (execute_builtin(cmd, mini));
	else
	{
		pid = fork();
		if (pid == 0)
		{
			// Child process
			if (mini->input_fd != STDIN_FILENO)
			{
				dup2(mini->input_fd, STDIN_FILENO);
				close(mini->input_fd);
			}
			if (mini->output_fd != STDOUT_FILENO)
			{
				dup2(mini->output_fd, STDOUT_FILENO);
				close(mini->output_fd);
			}
			set_redir(cmd);
			execute_external_cmd(cmd, mini);
		}
		else if (pid < 0)
		{
			// Fork failed
			perror("fork");
			return (1);
		}
		else
		{
			// Parent process
			waitpid(pid, &status, 0);
			*get_exit_status() = WEXITSTATUS(status);
		}
	}
	return (0);
}

/**
 * Executes multiple commands.
 * @param mini
 * @return
 */
int	execute_multiple_cmds(t_shell *mini)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		status;
	pid_t	pid;
	int		prev_fd;

	cmd = mini->cmds;
	prev_fd = STDIN_FILENO;
	status = 0;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
		{
			// Child process
			if (prev_fd != STDIN_FILENO)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->next)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			set_redir(cmd);
			if (is_builtin(cmd->cmd[0], mini->builtin_cmds))
				exit(execute_builtin(cmd, mini));
			else
				execute_external_cmd(cmd, mini);
		}
		// Parent process
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		if (!cmd->next)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				*get_exit_status() = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*get_exit_status() = 128 + WTERMSIG(status);
		}
		cmd = cmd->next;
	}
	// Wait for all child processes to finish
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			*get_exit_status() = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*get_exit_status() = 128 + WTERMSIG(status);
	}
	return (status);
}

/**
 * Handles built-in and external commands.
 * @param mini
 */
void	execute_cmd(t_shell *mini)
{
	t_cmd	*cmd;
	char	*expanded_cmd;
	int		i;

	mini->builtin_cmds = init_builtin_cmds();
	if (!mini->builtin_cmds)
	{
		perror("init_builtin_cmds");
		exit(EXIT_FAILURE);
	}
	cmd = mini->cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
		{
			expanded_cmd = expand_env_vars(cmd->cmd[i]);
			free(cmd->cmd[i]);
			cmd->cmd[i] = expanded_cmd;
			i++;
		}
		cmd = cmd->next;
	}
	if (mini->cmds && mini->cmds->next)
		execute_multiple_cmds(mini);
	else if (mini->cmds)
	{
		mini->input_fd = STDIN_FILENO;
		mini->output_fd = STDOUT_FILENO;
		execute_single_cmd_with_redir(mini->cmds, mini);
	}
	free_builtin_cmds(mini->builtin_cmds);
}
