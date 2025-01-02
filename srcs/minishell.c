/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/02 18:01:54 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Tanya, I made free function shorter and I moved your fre_exit function to memory_utils.c with others, 
// we can check later and leave which is shorter and works better. Alima

void	execute_cmd(t_shell *mini)
{
	char *args[3]; // array to hold cmnd and arg (echo + arg)
	// check if the cmnd is echo
	if (ft_strncmp(mini->args->arg_val, "echo", 4) == 0)
	{
		args[0] = mini->args->arg_val; // 1st arg is the cmnd
		// check if there is a next arg
		if (mini->args->next != NULL)
			args[1] = mini->args->next->arg_val; // 2nd arg (if exists)
		else
			args[1] = NULL; // no 2nd arg
		args[2] = NULL;     // Null-terminate the arg list
		// execute the echo cmnd
		builtin_echo(args);
	}
	else
		printf("Command not recognized.\n");
}

// int	main(int ac, char *av[])
// {
// 	t_shell mini; // shell structure to hold input and args
// 	mini.env_dup = NULL; // init env copy
// 	mini.args = NULL;     // init args
// 	// ignore unused params
// 	(void)av;
// 	(void)ac;
// 	// main loop for the shell
// 	while (1)
// 	{
// 		// read input from the user
// 		parser(&mini, mini.env_dup); // read input and process it

// // короче, ниже закоменченный код (1) если ты его используешь программа на echo hello
// // работает, затем выводит ошибку reading output и потом полность выходит из минишелла
// // (2) если не используешь, программа делает операцию echo hello дважды, НО полностью
// // не выходит из минишелла и можно там работать дальше

// 		if (!mini.input)
// 		{
// 			perror("Error reading input");
// 			break ;
// 		}
// 		// process the input into args
// 		mini.args = process_args(&mini);
// 		if (mini.args)
// 			execute_cmnd(&mini);
// 		free(mini.input);  // free the input line after processing
// 		mini.input = NULL; // reset input for the next iteration
// 	}
// 	// cleanup and exit
// 	free_exit(&mini, *exit_status()); // free resources and exit
// 	return (0);
// }

/**
 * t_shell	*mini; // Declare a pointer to a shell structure
 * 'av & av' is not used, so it's explicitly ignored
 * rl_outstream = stderr; // Redirect the output stream of the readline library to standard error
 */

// new main

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell_context; //we can change to another, understandable variable

	(void)ac; 
	(void)av; 
	*exit_status() = 0; 
	rl_outstream = stderr;
	shell_context = mem_allocator(sizeof(t_shell)); // Allocate memory for the 'shell_context' structure
	init(shell_context); // Initialize the 'shell_context' structure (setting up necessary fields)
	shell_context->env_dup = copy_envp(envp); // Copy the environment variables into 'shell_context->env_dup'
	shell_level_up(shell_context); // Increment the shell level in the environment (commonly used for the SHELL variable)
	// Main loop to keep running the shell interactively
	while (1)
	{
		//TODO add signals interactive
		parser(shell_context, shell_context->env_dup); // Parse user input (which will be stored in 'shell_context') using the copied environment
		//TODO add signals non-interactive
		// If there are commands in 'shell_context->cmds', execute them
		if (shell_context->cmds)
			execute_cmd(shell_context); // Execute cmds stored in 'shell_context->cmds'
		free_shell_mem(shell_context); // Free memory used by the 'shell_context' structure (such as args or cmds)
	}
	free_shell_mem(shell_context); // unreachable in infinite loop, but with signal (TODO) or exit it frees the resources before exiting
	return (0); // Return 0 to indicate successful program termination
}
