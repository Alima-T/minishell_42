/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:42:43 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/05 13:50:19 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//initialize a t_shell structure. TODO create another file for init and move it. Alima
// Таня: добавила параметр, изменила 2ю строчку в функции
void	init(t_shell *mini, char **envp)
{
	mini->input = NULL;
	mini->env_dup = copy_envp(envp);
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
// Таня: добавила 2 строчки - env_destroy, free
void	free_shell_mem(t_shell *mini)
{
	env_destroy(&mini->env_dup);
	list_destroy(&mini->args);
	cmd_destroy(&mini->cmds);
	free(mini);
}

//check if necessery, if not - delete
// /**
//  * Frees all allocated resources in the shell structure and exits the program.
//  *
//  * @param mini A pointer to the shell structure.
//  * @param exit_status The exit status code to return.
//  */
// void	free_exit(t_shell *mini, int exit_status)
// {
// 	// Free the argument list
// 	if (mini->args)
// 	{
// 		list_destroy(&mini->args);
// 			// Assuming list_destroy frees the argument list
// 	}
// 	// Free the input string if it was allocated
// 	if (mini->input)
// 	{
// 		free(mini->input);
// 		mini->input = NULL;
// 	}
// 	// Free any other resources in the shell structure
// 	// For example, if you have an environment copy, free it here
// 	if (mini->env_dup)
// 	{
// 		// Assuming env_dup is a linked list or an array of strings
// 		// Free each environment variable if necessary
// 		// Example: free_env_list(mini->env_dup);
// 	}
// 	// Exit the program with the specified exit status
// 	exit(exit_status);
// }
