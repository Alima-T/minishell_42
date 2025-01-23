/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:45:00 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/23 20:51:09 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Initializes the linked list of built-in commands.
 * @param
 * @return
 */
t_builtin_cmd	*init_builtin_cmds(void)
{
	t_builtin_cmd	*head;
	t_builtin_cmd	*new_node;
	int				i;
	const char		*cmds[] = {"cd", "echo", "env", "exit", "export", "pwd",
				"unset", NULL};

	head = NULL;
	i = 0;
	while (cmds[i] != NULL)
	{
		new_node = (t_builtin_cmd *)malloc(sizeof(t_builtin_cmd));
		if (!new_node)
			return (NULL);
		new_node->cmd = ft_strdup(cmds[i]);
		new_node->next = head;
		head = new_node;
		i++;
	}
	return (head);
}

/**
 * Counts the number of arguments in a command.
 * @param args
 * @return
 */
int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

/**
 * Checks if a command is a built-in command.
 * @param cmd
 * @param builtin_cmds
 * @return
 */
int	is_builtin(const char *cmd, t_builtin_cmd *builtin_cmds)
{
	t_builtin_cmd	*current;

	current = builtin_cmds;
	while (current)
	{
		if (ft_strcmp(cmd, current->cmd) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * @param env_dup
 * @return
 */
char	**env_list_to_array(t_env *env_dup)
{
	int		size;
	int		i;
	char	**envp;
	t_env	*current;

	size = env_dup_size(env_dup);
	i = 0;
	envp = malloc(sizeof(char *) * (size + 1));
	current = env_dup;
	while (current)
	{
		envp[i] = ft_strdup(current->line);
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

/**
 * @param cmd
 * @return
 */
char	*find_executable(char *cmd)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, cmd);
		free(path);
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
