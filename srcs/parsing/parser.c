/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:51:57 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/19 16:08:49 by tbolsako         ###   ########.fr       */
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
// int	parser(t_shell *mini, t_env *env_dup)
// {
// 	(void)env_dup;

// 	mini->input = safe_readline(BEGIN "minishell-1.0$ " CLOSE);// get input from the user
// 	if (!mini->input)// handle EOF (ctrl + D)
// 	{
// 		// write(STDOUT_FILENO, "exit\n",
// 5);// Write to both stdout and stderr to ensure visibility
// 		// free_shell_mem_enhanced(mini);	// clean up and exit
// 		// shell_level_down(mini);
// 		// exit(*get_exit_status());
// 		printf("exit\n");
// 		exit(*get_exit_status());
// 	}
// 	if (mini->input[0] != '\0')// add non-empty inputs to history
// 		add_history(mini->input);
// 	if (mini->input[0] == '\0')// empty input - nothing to do
// 	{
// 		free(mini->input);
// 		mini->input = NULL;
// 		return (0);
// 	}
// 	if (validator(mini->input) == 0)// validate the input syntax
// 	{
// 		mini->args = args_process(mini);// process input into arguments
// 		if (!mini->args)
// 		{
// 			free(mini->input);
// 			mini->input = NULL;
// 			return (1);
// 		}
// 		mini->cmds = cmds_process(mini);// process arguments into commands
// 		if (!mini->cmds && mini->args)
// 		{
// 			arglst_destroy(&mini->args);// command processing failed
// 			free(mini->input);
// 			mini->input = NULL;
// 			return (1);
// 		}
// 	}
// 	else
// 	{
// 		// input validation failed
// 		// ft_putstr_fd(BEGIN "minishell-1.0$ " CLOSE, STDERR_FILENO);
// 		*get_exit_status() = 2;
// 		free(mini->input);
// 		mini->input = NULL;
// 		return (2);
// 	}
// 	free(mini->input);// free the input string as it's no longer needed
// 	mini->input = NULL;
// 	return (0);
// }

int	parser(t_shell *mini, t_env *env_dup)
{
	int	status;

	(void)env_dup;
	// get input from the user
	mini->input = safe_readline(BEGIN "minishell-1.0$ " CLOSE);
	if (!mini->input)
	// handle EOF (ctrl + D)
	{
		// printf("exit\n");
		// exit(*get_exit_status());
		// Write exit and newline to match bash's behavior
		// write(STDIN_FILENO, "exit\n", 5);
		status = *get_exit_status();
		// mini->input = safe_readline(BEGIN "minishell-1.0$ " CLOSE "exit");
		// Call our silent exit function
		silent_exit(mini, status);
	}
	if (mini->input[0] != '\0') // add non-empty inputs to history
		add_history(mini->input);
	if (mini->input[0] == '\0') // empty input - nothing to do
	{
		free(mini->input);
		mini->input = NULL;
		return (0);
	}
	valid_helper(mini);
	free(mini->input); // free the input string as it's no longer needed
	mini->input = NULL;
	return (0);
}

int	valid_helper(t_shell *mini) // TO DO Alima, make shorter
{
	if (validator(mini->input) == 0)
	{
		mini->args = args_process(mini); // process input into arguments
		if (!mini->args)
		{
			free(mini->input);
			mini->input = NULL;
			return (1);
		}
		mini->cmds = cmds_process(mini); // process arguments into commands
		if (!mini->cmds && mini->args)
		{
			arglst_destroy(&mini->args); // command processing failed
			free(mini->input);
			mini->input = NULL;
			return (1);
		}
	}
	else // input validation failed
	{
		// ft_putstr_fd(BEGIN "minishell-1.0$ " CLOSE, STDERR_FILENO);//?
		*get_exit_status() = 2;
		free(mini->input);
		mini->input = NULL;
		return (2);
	}
	return (0);
}
