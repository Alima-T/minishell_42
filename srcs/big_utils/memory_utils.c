/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:42:43 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/02 15:38:27 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
function to safely allocate memory using malloc. 
If the allocation fails, prints an err_msg and exits
*/
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

//frees arrays
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


// Frees the list of args and the list or structure of cmds

void	free_shell_mem(t_shell *mini)
{
	argslst_destroy(&mini->args);
	cmdslst_destroy(&mini->cmds);
}