/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:17:08 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/18 15:26:09 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Handles the execution of external commands.
 * @param cmd Command structure
 * @param mini Shell structure
 * @return Does not return - either executes or exits
 */
static int	execute_external_cmd(t_cmd *cmd, t_shell *mini)
{
	char	**envp;
	char	*executable;

	envp = env_list_to_array(mini->env_dup);
	if (!envp)
	{
		perror("env_list_to_array");
		exit(1);
	}
	if (ft_strchr(cmd->cmd[0], '/'))
	{
		if (access(cmd->cmd[0], F_OK) != 0)
		{
			ft_putstr_fd(BEGIN "minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			free_array(envp);
			exit(127);
		}
		else if (access(cmd->cmd[0], X_OK) != 0)
		{
			ft_putstr_fd(BEGIN"minishell: "CLOSE, STDERR_FILENO);
			ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			free_array(envp);
			exit(126);
		}
		executable = ft_strdup(cmd->cmd[0]);
	}
	else
	{
		executable = find_executable(cmd->cmd[0], mini->env_dup);
		if (!executable)
		{
			ft_putstr_fd(BEGIN "minishell: "CLOSE, STDERR_FILENO);
			ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			free_array(envp);
			exit(127);
		}
	}
	execve(executable, cmd->cmd, envp);
	perror("execve");
	free_array(envp);
	free(executable);
	exit(EXIT_FAILURE);
}

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
	int	result;

	saved_stdout = dup(STDOUT_FILENO);
	if (!cmd->fork && is_builtin(cmd->cmd[0], mini->builtin_cmds))
	{
		if (setup_redirections(cmd) != 0)
		{
			*get_exit_status() = 1;
			close(saved_stdout);
			return (1);
		}
		result = execute_builtin(cmd, mini);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return (result);
	}
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		cmd->fork = 1;
		close(saved_stdout);
		if (setup_redirections(cmd) != 0)
			exit(1);
		if (is_builtin(cmd->cmd[0], mini->builtin_cmds))
			exit(execute_builtin(cmd, mini));
		else
			execute_external_cmd(cmd, mini);
	}
	else if (cmd->pid < 0)
	{
		ft_putstr_fd(BEGIN "minishell: "CLOSE, STDERR_FILENO);
		ft_putendl_fd("fork: Resource temporarily unavailable", STDERR_FILENO);
		close(saved_stdout);
		return (1);
	}
	waitpid(cmd->pid, &status, 0);
	cleanup_cmd(cmd);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
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

	if (create_pipes(mini->cmds) != 0)
		return (1);
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
	return (*get_exit_status());
}

/**
 * Main command execution function that handles built-ins, signaks,
	and pipelines
 * @param mini Shell structure conatining commands and environment
 */
void	execute_cmd(t_shell *mini)
{
	t_cmd	*cmd;
	char	*expanded_cmd;
	int		i;

	mini->builtin_cmds = init_builtin_cmds();
	if (!mini->builtin_cmds)
	{
		ft_putstr_fd(BEGIN "minishell-1.0: "CLOSE, STDERR_FILENO);
		ft_putendl_fd("failed to initialize built-in commands", STDERR_FILENO);
		*get_exit_status() = 1;
		return ;
	}
	cmd = mini->cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
		{
			expanded_cmd = expand_env_vars(cmd->cmd[i], mini->env_dup);
			if (!expanded_cmd)
			{
				ft_putstr_fd(BEGIN "minishell: "CLOSE, STDERR_FILENO);
				ft_putendl_fd("expansion error", STDERR_FILENO);
				free_builtin_cmds(mini->builtin_cmds);
				*get_exit_status() = 1;
				return ;
			}
			free(cmd->cmd[i]);
			cmd->cmd[i] = expanded_cmd;
			i++;
		}
		cmd = cmd->next;
	}
	cmd = mini->cmds;
	while (cmd)
	{
		if (set_heredoc(cmd) != 0)
		{
			free_builtin_cmds(mini->builtin_cmds);
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
