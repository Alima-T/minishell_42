/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:45:00 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/17 18:52:43 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Converts environment linked list to array format for execve
 * @param env_dup Environment linked list
 * @return Array of environment variables or NULL on error
 */
char	**env_list_to_array(t_env *env_dup)
{
	int		size;
	int		i;
	char	**envp;
	t_env	*current;

	if (!env_dup)
		return (NULL);
	size = count_env_vars(env_dup);
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	current = env_dup;
	i = 0;
	while (current && i < size)
	{
		envp[i] = ft_strdup(current->line);
		if (!envp[i])
		{
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}

/**
 * Searches for executable in PATH or uses absolute path
 * @param cmd Command name
 * @return Path to executable or NULL if not found
 */
char	*find_executable(char *cmd, t_env *env_dup)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;
	t_env	*path_env;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path_env = env_dup;
	while (path_env)
	{
		if (ft_strcmp(path_env->key, "PATH") == 0)
			break ;
		path_env = path_env->next;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env->val, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
		{
			free_array(paths);
			return (NULL);
		}
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (!full_path)
		{
			free_array(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}
