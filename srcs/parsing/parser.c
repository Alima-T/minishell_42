/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:51:57 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/17 19:10:53 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*safe_readline(const char *prompt)
{
	char	*line;

	struct termios term, old_term;
	// Save original terminal settings
	tcgetattr(STDIN_FILENO, &old_term);
	// Make a copy to modify
	term = old_term;
	// Ensure terminal is in canonical mode with echo
	term.c_lflag |= (ICANON | ECHO);
	// Apply settings before readline
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// Use readline to get input
	line = readline(prompt);
	// Restore original terminal settings
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	return (line);
}

// /**
//  * Validates the input string for the shell.
//  * @param input The input string to validate.
//  * @return 0 if the input is valid, -1 if invalid.
//  */
int	parser(t_shell *mini, t_env *env_dup)
{
	(void)env_dup;
	// get input from the user
	mini->input = safe_readline(BEGIN "msh-1.0$ " CLOSE);
	// handle EOF (ctrl + D)
	if (!mini->input)
	{
		// Write to both stdout and stderr to ensure visibility
		write(STDOUT_FILENO, "exit\n", 5);
		// clean up and exit
		free_shell_mem_enhanced(mini);
		shell_level_down(mini);
		exit(*get_exit_status());
	}
	// add non-empty inputs to history
	if (mini->input[0] != '\0')
		add_history(mini->input);
	// empty input - nothing to do
	if (mini->input[0] == '\0')
	{
		free(mini->input);
		mini->input = NULL;
		return (0);
	}
	// validate the input syntax
	if (validator(mini->input) == 0)
	{
		// process input into arguments
		mini->args = args_process(mini);
		if (!mini->args)
		{
			free(mini->input);
			mini->input = NULL;
			return (1);
		}
		// process arguments into commands
		mini->cmds = cmds_process(mini);
		if (!mini->cmds && mini->args)
		{
			// command processing failed
			arglst_destroy(&mini->args);
			free(mini->input);
			mini->input = NULL;
			return (1);
		}
	}
	else
	{
		// input validation failed
		ft_putstr_fd(BEGIN "msh-1.0$: " CLOSE, STDERR_FILENO);
		*get_exit_status() = 2;
		free(mini->input);
		mini->input = NULL;
		return (2);
	}
	// free the input string as it's no longer needed
	free(mini->input);
	mini->input = NULL;
	return (0);
}
