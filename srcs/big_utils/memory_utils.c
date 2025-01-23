/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:42:43 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/23 18:17:11 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
initialize a t_shell structure. TODO create another file for init and move it.
Alima
*/
void	init(t_shell *mini)
{
	mini->input = NULL;
	mini->env_dup = NULL;
	mini->cmds = NULL;
	mini->args = NULL;
}

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

/*
Frees the list of args and the list or structure of cmds
*/

void	free_shell_mem(t_shell *mini)
{
	list_destroy(&mini->args);
	cmd_destroy(&mini->cmds);
}

//reapeat func (Alima)
//free arrays
void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
