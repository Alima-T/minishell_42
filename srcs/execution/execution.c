/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:17:08 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/06 19:33:27 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to handle the execution of external commands
int	execute_external_cmd(t_cmd *cmd, t_shell *mini)
{
	char	**envp;
	char	*executable;

	envp = env_list_to_array(mini->env_dup);
	executable = find_executable(cmd->cmd[0]);
	if (!executable)
	{
		printf("minishell: command not found: %s\n", cmd->cmd[0]);
		free_env_array(envp);
		// return 127 for command not found
		return (127);
	}
	execve(executable, cmd->cmd, envp);
	perror("execve");
	free_env_array(envp);
	free(executable);
	exit(EXIT_FAILURE);
}

// function to execute a built-in command
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
		return (builtin_exit(cmd_count, cmd->cmd));
	free_env_array(env_array);
	return (1);
}

// function to execute a single command
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

// function to execute multiple commands
int	execute_multiple_cmds(t_shell *mini)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		status;

	cmd = mini->cmds;
	mini->input_fd = STDIN_FILENO;
	status = 0;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				return (1);
			}
			mini->output_fd = pipe_fd[1];
			status = execute_single_cmd_with_redir(cmd, mini);
			close(pipe_fd[1]);
			mini->input_fd = pipe_fd[0];
		}
		else
		{
			mini->output_fd = STDOUT_FILENO;
			status = execute_single_cmd_with_redir(cmd, mini);
		}
		cmd = cmd->next;
	}
	if (mini->input_fd != STDIN_FILENO)
		close(mini->input_fd);
	return (status);
}

// function to handle built-in and external commands
void	execute_cmd(t_shell *mini)
{
	mini->builtin_cmds = init_builtin_cmds();
	if (!mini->builtin_cmds)
	{
		perror("Failed to initialize built-in commands");
		return ;
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
