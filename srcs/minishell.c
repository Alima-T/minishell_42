/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/06 15:56:31 by aokhapki         ###   ########.fr       */
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
	t_shell	*mini;

	(void)ac;
	(void)av;
	*exit_status() = 0;
	rl_outstream = stderr;
	mini = mem_allocator(sizeof(t_shell));
	init(mini);
	mini->env_dup = copy_envp(envp);
	shell_level_up(mini);
	while (1)
	{
		sigs_interact_shell();
		parser(mini, mini->env_dup);
		sigs_non_interact_shell();
		if (mini->cmds)
		{
			execute_cmd(mini);
		}
		free_shell_mem(mini);
	}
	free_shell_mem(mini);
	return (0);
}


