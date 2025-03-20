/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:45:00 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 14:55:40 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static t_env	*find_path_env(t_env *env_dup)
{
	t_env	*path_env;

	path_env = env_dup;
	while (path_env)
	{
		if (ft_strcmp(path_env->key, "PATH") == 0)
			return (path_env);
		path_env = path_env->next;
	}
	return (NULL);
}

static char	*try_path(char *dir_path, char *cmd)
{
	char	*path;
	char	*full_path;

	path = ft_strjoin(dir_path, "/");
	if (!path)
		return (NULL);
	full_path = ft_strjoin(path, cmd);
	free(path);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*executable;

	i = 0;
	while (paths[i])
	{
		executable = try_path(paths[i], cmd);
		if (executable)
		{
			free_array(paths);
			return (executable);
		}
		i++;
	}
	free_array(paths);
	return (NULL);
}

/**
 * Searches for executable in PATH or uses absolute path
 * @param cmd Command name
 * @return Path to executable or NULL if not found
 */
char	*find_executable(char *cmd, t_env *env_dup)
{
	char	**paths;
	char	*direct_exe;
	t_env	*path_env;

	direct_exe = check_direct_path(cmd);
	if (direct_exe)
		return (direct_exe);
	path_env = find_path_env(env_dup);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env->val, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
