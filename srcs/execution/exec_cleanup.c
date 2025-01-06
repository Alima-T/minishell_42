/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:56:52 by tbolsako          #+#    #+#             */
/*   Updated: 2025/01/06 19:19:23 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to free the linked list of built-in commands
void	free_builtin_cmds(t_builtin_cmd *builtin_cmds)
{
	t_builtin_cmd	*current;
	t_builtin_cmd	*next;

	current = builtin_cmds;
	while (current)
	{
		next = current->next;
		free(current->cmd);
		free(current);
		current = next;
	}
}

// function to free the array of env vars
void	free_env_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
