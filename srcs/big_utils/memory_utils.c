/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:42:43 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 16:55:48 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*mem_allocator(size_t size)
{
	void	*allocated_mem;

	allocated_mem = (void *)malloc(size);
	if (!allocated_mem)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	return (allocated_mem);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

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

void	free_shell_mem_enhanced(t_shell *mini)
{
	t_cmd	*current;

	if (!mini)
		return ;
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
	arglst_destroy(&mini->args);
	if (mini->cmds)
	{
		current = mini->cmds;
		while (current)
		{
			cleanup_cmd(current);
			current = current->next;
		}
		cmdlst_destroy(&mini->cmds);
	}
	if (mini->builtin_cmds)
	{
		free_builtin_cmds(mini->builtin_cmds);
		mini->builtin_cmds = NULL;
	}
}
