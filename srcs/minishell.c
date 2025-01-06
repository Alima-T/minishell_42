/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/06 14:28:17 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	// Allocate memory for the 'mini' structure
	mini = mem_allocator(sizeof(t_shell));
	// Initialize the 'mini' structure (setting up necessary fields)
	init(mini);
	// Copy the environment variables into 'mini->env_dup'
	mini->env_dup = copy_envp(envp);
	// Increment the shell level in the environment (commonly used for the SHELL variable)
	shell_level_up(mini);
	// handle signals
	setup_signal_handlers();
	// Main loop to keep running the shell interactively
	while (1)
	{
		//TODO add signals interactive
		// Parse user input (which will be stored in 'mini') using the copied environment
		parser(mini, mini->env_dup);
		//TODO add signals non-interactive
		// If there are commands in 'mini->cmds', execute them
		if (mini->args)
		{
			mini->cmds = cmds_processing(mini);
			// Execute cmds stored in 'mini->cmds'
			execute_cmd(mini);
			cmd_destroy(&mini->cmds);
			list_destroy(&mini->args);
		}
		// Free memory used by the 'mini' structure (such as args or cmds)
		free_shell_mem(mini);
	}
	// unreachable in infinite loop, but with signal (TODO) or exit it frees the resources before exiting
	free_shell_mem(mini);
	// Return 0 to indicate successful program termination
	return (0);
}
