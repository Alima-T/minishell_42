/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:47:13 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/17 19:03:42 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Summary of the Function:
Purpose: The cmds_process function processes a linked list of arguments from a shell structure (t_shell *mini) and creates a list of commands (t_cmd) based on the presence of pipe characters (|).
Logic:
It first checks if there are any arguments. If not, it returns NULL.
It initializes pointers to traverse the argument list and to mark the beginning of each command.
It loops through the arguments,
	checking for pipe characters. When a pipe is found,
	it creates a command from the arguments collected so far and updates the starting point for the next command.
After the loop,
	it ensures that the last segment of arguments is also processed into a command.
Return Value: The function returns a linked list of commands created from the input arguments.
*/

// Replaces an environment variable in the input string with its corresponding value.
// It extracts the key from the input, retrieves its value from the environment,
// and constructs a new string with the substituted value.
char	*replace_env(char *input, int start, int end, t_env *env_dup)
{
	char	*result;

	char *tmp1; // Temporary string for the part before the variable
	char *tmp2; // Temporary string for the value of the variable
	char *tmp3; // Temporary string for the part after the variable
	char *key;  // The key of the environment variable
	// Extract the environment variable key from the input string.
	// The key starts after the '$' symbol and ends at the position of 'end'.
	// We take a substring from 'start + 1' to 'end - start
	//	- 1' to get the key.
	tmp1 = ft_substr(input, 0, start);
	// Check if we're dealing with ${VAR} syntax
	if (input[start + 1] == '{' && input[end - 1] == '}')
	{
		// Extract between { and }
		key = ft_substr(input, start + 2, end - start - 3);
	}
	else
	{
		// Regular $VAR extraction
		key = ft_substr(input, start + 1, end - start - 1);
	}
	// Extract the variable key
	tmp2 = find_in_env(env_dup, key);
	if (tmp2)
	{
		// Find the value of the variable in the environment
		tmp2 = ft_strdup(tmp2);
	}
	else
		tmp2 = ft_strdup("");
	// Get the part after the variable
	tmp3 = ft_strdup(input + end);
	// Join all three parts (before, value, after)
	result = ft_strjoin_con(tmp1, tmp2, tmp3);
	// Free the temporary strings to avoid memory leaks
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(key);
	free(input);
	// Return the new input string with the variable replaced
	return (result);
}

// This function handles the case when a question mark is encountered in the input string.
// It retrieves the current value of g_ext_stats,
// constructs a new string with this value,
// and resets g_ext_stats to 0.
char	*question_handle(char *input, int start, int *i)
{
	char *line_new; // New string to hold the modified input
	char *tmp_1;    // Temporary string for the part before the question mark
	char *tmp_2;    // Temporary string for the concatenated result
	char *nbr_val;  // String representation of the exit status
	char *tail;     // Part of the input string after the question mark
	nbr_val = ft_itoa(*get_exit_status());
	// Convert the exit status to a string
	tmp_1 = ft_substr(input, 0, start);
	// Get the part before the question mark
	tmp_2 = ft_strjoin(tmp_1, nbr_val);
	// Concatenate the part before with the exit status
	tail = ft_strdup(&input[*i]);
	// Get the part of the input after the question mark
	line_new = ft_strjoin(tmp_2, tail);
	// Concatenate the exit status with the tail
	free(nbr_val);
	// Free the string representation of the exit status
	free(tmp_1);
	// Free the temporary string for the part before
	free(tmp_2);
	// Free the temporary string for the concatenated result
	free(tail);  // Free the tail part of the input
	free(input); // Free the original input string
	return (line_new);
	// Return the new input string with the exit status
}

// If a char is a valid (underscore or alphanumeric). Returns 0 - if not valid
char	is_valid_char(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

// Check for dollar in the input string and determines if they represent
// an environment variable or a special case ("?"). Updates the iterator
// and calls the appropriate handler function to process the input.
char	*is_dollar(char *input, int *i, t_env *env_dup)
{
	int	start;
	int	key_start;
	int	key_end;

	// Set the begin to current index
	start = *i;
	if (ft_strchr("?", input[start + 1]))
	{
		*i += 2;
		return (question_handle(input, start, i));
	}
	// Check for ${VAR} syntax
	if (input[start + 1] == '{')
	{
		// Skip the opening brace
		(*i)++;
		// Find closing brace
		while (input[++(*i)])
		{
			if (input[*i] == '}')
			{
				// Include closing brace in the range
				(*i)++;
				break ;
			}
			// Bail if we hit unexpected characters inside braces
			if (!is_valid_char(input[*i]) && input[*i] != '}')
				return (input);
		}
		// If we didn't find a closing brace, return original
		if (input[*i - 1] != '}')
			return (input);
		// Extract key without braces and replace
		// Start after ${
		key_start = start + 2;
		// End before }
		key_end = *i - 1;
		// Empty variable name
		if (key_end <= key_start)
			return (input);
		// Adjust start and end to account for braces
		return (replace_env(input, start, *i, env_dup));
	}
	// Loop to find the end of the variable name
	while (input[++(*i)])
	{
		if (!is_valid_char(input[*i]))
			break ;
	}
	// If no valid variable name was found
	if (*i == start + 1)
		return (input);
	// Replace the environment variable in the input
	input = replace_env(input, start, *i, env_dup);
	return (input);
}
