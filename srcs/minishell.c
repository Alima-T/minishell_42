/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/05 16:45:02 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Tanya, I made free function shorter and I moved your fre_exit function to memory_utils.c with others, 
// we can check later and leave which is shorter and works better. Alima

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
	// we can change to another, understandable variable
	t_shell	*mini;

	(void)ac;
	(void)av;
	*exit_status() = 0;
	rl_outstream = stderr;
	// Allocate memory for the 'shell_context' structure
	mini = mem_allocator(sizeof(t_shell));
	// Initialize the 'shell_context' structure (setting up necessary fields)
	init(mini, envp);
	// Copy the environment variables into 'shell_context->env_dup'
	mini->env_dup = copy_envp(envp);
	// Increment the shell level in the environment (commonly used for the SHELL variable)
	shell_level_up(mini);
	// handle signals
	setup_signal_handlers();
	// Main loop to keep running the shell interactively
	while (1)
	{
		//TODO add signals interactive
		// Parse user input (which will be stored in 'shell_context') using the copied environment
		parser(mini, mini->env_dup);
		//TODO add signals non-interactive
		// If there are commands in 'shell_context->cmds', execute them
		if (mini->args)
		{
			mini->cmds = cmds_processing(mini);
			// Execute cmds stored in 'mini->cmds'
			execute_cmd(mini);
			cmd_destroy(&mini->cmds);
			list_destroy(&mini->args);
		}
		// Free memory used by the 'shell_context' structure (such as args or cmds)
		free_shell_mem(mini);
	}
	// unreachable in infinite loop, but with signal (TODO) or exit it frees the resources before exiting
	free_shell_mem(mini);
	// Return 0 to indicate successful program termination
	return (0);
}
