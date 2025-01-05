/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:17:08 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/05 17:37:08 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to handle the execution of external commands
int	execute_external_cmd(t_cmd *cmd, t_env *env_dup)
{
	pid_t	pid;
	int		status;
	char	**envp;
	char	*executable;

	envp = env_list_to_array(env_dup);
	executable = find_executable(cmd->cmd[0]);
	if (!executable)
	{
		perror("execve");
		free_env_array(envp);
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		// Child process
		if (cmd->inp != STDIN_FILENO)
		{
			dup2(cmd->inp, STDIN_FILENO);
			close(cmd->inp);
		}
		if (cmd->out != STDOUT_FILENO)
		{
			dup2(cmd->out, STDOUT_FILENO);
			close(cmd->out);
		}
		execve(executable, cmd->cmd, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		// Fork failed
		perror("fork");
		free(executable);
		free_env_array(envp);
		return (1);
	}
	else
	{
		// Parent process
		waitpid(pid, &status, 0);
		*exit_status() = WEXITSTATUS(status);
	}
	free(executable);
	free_env_array(envp);
	return (0);
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
int	execute_single_cmd(t_cmd *cmd, t_shell *mini, t_builtin_cmd *builtin_cmds)
{
	if (is_builtin(cmd->cmd[0], builtin_cmds))
		return (execute_builtin(cmd, mini));
	else
		return (execute_external_cmd(cmd, mini->env_dup));
}

// function to execute multiple commands
int	execute_multiple_cmds(t_shell *mini, t_builtin_cmd *builtin_cmds)
{
	t_cmd	*cmd;
	int		status;

	cmd = mini->cmds;
	status = 0;
	while (cmd)
	{
		status = execute_single_cmd(cmd, mini, builtin_cmds);
		cmd = cmd->next;
	}
	return (status);
}

// function to handle built-in and external commands
void	execute_cmd(t_shell *mini)
{
	t_builtin_cmd	*builtin_cmds;

	builtin_cmds = init_builtin_cmds();
	if (!builtin_cmds)
	{
		perror("Failed to initialize built-in commands");
		return ;
	}
	if (mini->cmds && mini->cmds->next)
		execute_multiple_cmds(mini, builtin_cmds);
	else if (mini->cmds)
		execute_single_cmd(mini->cmds, mini, builtin_cmds);
	free_builtin_cmds(builtin_cmds);
}
