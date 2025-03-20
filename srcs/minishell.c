/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:34:37 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 19:48:11 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Initialize shell structure with default values
 * @param mini Pointer to shell structure
 */
void	init(t_shell *mini)
{
	mini->input = NULL;
	mini->env_dup = NULL;
	mini->cmds = NULL;
	mini->args = NULL;
	mini->builtin_cmds = NULL;
}

/**
 * Main shell loop function
 * @param mini Shell structure
 * @return Final exit status
 */
int	shell_loop(t_shell *mini)
{
	int	parse_result;

	while (1)
	{
		sigs_interact_shell();
		parse_result = parser(mini, mini->env_dup);
		if (parse_result != 0)
		{
			free_shell_mem_enhanced(mini);
			continue ;
		}
		if (mini->cmds)
		{
			sigs_non_interact_shell();
			execute_cmd(mini);
		}
		free_shell_mem_enhanced(mini);
	}
	return (*get_exit_status());
}

/**
 * t_shell	*mini; // Declare a pointer to a shell structure
 * 'av & av' is not used, so it's explicitly ignored
 * rl_outstream = stderr;
 * Redirect the output stream of the readline library to standard error
 */
int	main(int ac, char **av, char **envp)
{
	t_shell	*mini;
	int		exit_code;

	(void)ac;
	(void)av;
	*get_exit_status() = 0;
	mini = mem_allocator(sizeof(t_shell));
	if (!mini)
		return (1);
	init(mini);
	mini->env_dup = copy_envp(envp);
	if (!mini->env_dup)
	{
		free(mini);
		return (1);
	}
	shell_level_up(mini);
	exit_code = shell_loop(mini);
	env_destroy(&mini->env_dup);
	free(mini);
	return (exit_code);
}
