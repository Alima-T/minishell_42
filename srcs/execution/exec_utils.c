/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:44:37 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/20 21:19:01 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**cleanup_env_array(char **envp, int i)
{
	while (--i >= 0)
		free(envp[i]);
	free(envp);
	return (NULL);
}

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
			return (cleanup_env_array(envp, i));
		i++;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	*save_std_fds(void)
{
	static int	saved_fds[2];

	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	return (saved_fds);
}

void	restore_std_fds(int *saved_fds)
{
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
}
