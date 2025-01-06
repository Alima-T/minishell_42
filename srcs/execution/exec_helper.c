/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:45:00 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/06 19:18:40 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to initialize the linked list of built-in commands
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

// function to count the num of args in a command
int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

// function to check if a command is a built-in command
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

char	*find_executable(char *cmd)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
