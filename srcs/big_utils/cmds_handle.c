/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:45:15 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/02 14:07:25 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//initialize a t_shell structure. 
void init(t_shell *mshell)
{
	mshell->input = NULL;
	mshell->env_copy = NULL;
	mshell->cmds = NULL;
	mshell->args = NULL;
}
/*
function to safely allocate memory using malloc. 
If the allocation fails, prints an err_msg and exits
*/
void *mem_allocator(size_t size)
{
	void *allocated_mem;
	allocated_mem = (void *)malloc(size);
	if(!allocated_mem)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	return allocated_mem;
}

/*
Frees the list of args and the list or structure of cmds
*/
void free_shell_mem(t_shell *mini)
{ 
	list_destroy(&mini->args);
	cmds_destroy(&mini->cmds);
}
