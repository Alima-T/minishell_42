/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:58:31 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 15:12:23 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_error_and_exit(char *cmd, char *message, int exit_code,
		char **envp)
{
	ft_putstr_fd(BEGIN "minishell: " CLOSE, STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	free_array(envp);
	exit(exit_code);
}

static int	check_file_access(char *cmd_path, char **envp)
{
	if (access(cmd_path, F_OK) != 0)
		print_error_and_exit(cmd_path, ": No such file or directory\n", 127,
			envp);
	else if (access(cmd_path, X_OK) != 0)
		print_error_and_exit(cmd_path, ": Permission denied\n", 126, envp);
	return (0);
}

static char	*get_direct_path(char *cmd, char **envp)
{
	char	*executable;

	check_file_access(cmd, envp);
	executable = ft_strdup(cmd);
	if (!executable)
	{
		free_array(envp);
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	return (executable);
}

static char	*get_path_from_env(char *cmd, t_env *env_dup, char **envp)
{
	char	*executable;

	executable = find_executable(cmd, env_dup);
	if (!executable)
		print_error_and_exit(cmd, ": command not found\n", 127, envp);
	return (executable);
}

/**
 * Handles the execution of external commands.
 * @param cmd Command structure
 * @param mini Shell structure
 * @return Does not return - either executes or exits
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
	if (ft_strchr(cmd->cmd[0], '/'))
		executable = get_direct_path(cmd->cmd[0], envp);
	else
		executable = get_path_from_env(cmd->cmd[0], mini->env_dup, envp);
	execve(executable, cmd->cmd, envp);
	perror("execve");
	free_array(envp);
	free(executable);
	exit(EXIT_FAILURE);
}
