/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:51:57 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/20 18:51:44 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Validates the input string for the shell.
 *
 * @param input The input string to validate.
 * @return 0 if the input is valid, -1 if invalid.
 */
int	validator(char *input)
{
	char	*trimmed_input;
	int		last_index;

	// Check for NULL input
	if (input == NULL)
		return (-1); // Invalid input
	// Trim leading and trailing whitespace
	// Trim spaces, tabs, and newlines
	trimmed_input = ft_strtrim(input, " \t\n");
	// Check if the trimmed input is empty
	if (ft_strlen(trimmed_input) == 0)
	{
		free(trimmed_input); // Free the trimmed input
		return (-1);         // Invalid input
	}
	// Check for invalid characters at the start and end
	if (trimmed_input[0] == ';' || trimmed_input[0] == '|')
	{
		free(trimmed_input); // Free the trimmed input
		return (-1);         // Invalid character found
	}
	last_index = ft_strlen(trimmed_input) - 1;
	if (trimmed_input[last_index] == ';' || trimmed_input[last_index] == '|')
	{
		free(trimmed_input); // Free the trimmed input
		return (-1);         // Invalid character found
	}
	// Check for invalid characters in the middle of the string
	if (ft_strchr(trimmed_input, ';') || ft_strchr(trimmed_input, '|'))
	{
		free(trimmed_input); // Free the trimmed input
		return (-1);         // Invalid character found
	}
	free(trimmed_input); // Free the trimmed input
	return (0);          // Valid input
}

void	parser(t_shell *mini, t_env *env_dup)
{
	(void)env_dup;
	// read input from the user
	mini->input = readline(BEGIN(49, 32) "[minishell ]$ " CLOSE);
	if (mini->input == NULL) // Check if readline returned NULL
	{
		if (mini->input == NULL && *mini->input == '\0')
			// Check for empty input
		{
			printf("Exiting shell.\n");
			exit(EXIT_SUCCESS); // Exit gracefully on EOF
		}
		perror("Error reading input"); // Print error message
		exit(EXIT_FAILURE);            // Exit on error
	}
	if (*mini->input)
		add_history(mini->input);
	if (validator(mini->input) == 0)
	{
		mini->args = process_args(mini);
		// mini->cmds = process_cmds(mini);
		execute_cmnd(mini); // Call the function to execute the command
	}
	free(mini->input);
	mini->input = NULL;
	return ;
}
