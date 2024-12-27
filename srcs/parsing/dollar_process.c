/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:47:13 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 15:36:21 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
Summary of the Function:
Purpose: The cmds_processing function processes a linked list of arguments from a shell structure (t_shell *mini) and creates a list of commands (t_cmd) based on the presence of pipe characters (|).
Logic:
It first checks if there are any arguments. If not, it returns NULL.
It initializes pointers to traverse the argument list and to mark the beginning of each command.
It loops through the arguments, checking for pipe characters. When a pipe is found, it creates a command from the arguments collected so far and updates the starting point for the next command.
After the loop, it ensures that the last segment of arguments is also processed into a command.
Return Value: The function returns a linked list of commands created from the input arguments.
*/
// Check if a character is a valid key character (underscore or alphanumeric).
char	is_valid_char(char c)
{
	if (c == '_' || ft_isalnum(c)) // Check if the character is an underscore or alphanumeric
		return (1); // Return 1 (true) if valid
	return (0); // Return 0 (false) if not valid
}

// Replaces an environment variable in the input string with its corresponding value.
// It extracts the key from the input, retrieves its value from the environment,
// and constructs a new string with the substituted value.
char	*replace_env_var(char *input, int start, int end, t_env *env_dup)
{
	char	*tmp1; // Temporary string for the part before the variable
	char	*tmp2; // Temporary string for the value of the variable
	char	*tmp3; // Temporary string for the part after the variable
	char	*key; // The key of the environment variable

	// Extract the environment variable key from the input string.
	// The key starts after the '$' symbol and ends at the position of 'end'.
	// We take a substring from 'start + 1' to 'end - start - 1' to get the key.
	tmp1 = ft_substr(input, 0, start); // Get the part before the variable
	key = ft_substr(input, start + 1, end - start - 1); // Extract the variable key
	tmp2 = ft_strdup(find_in_env(env_dup, key)); // Find the value of the variable in the environment
	tmp3 = ft_strdup(input + end); // Get the part after the variable
	free(input); // Free the original input string
	input = NULL; // Set input to NULL to avoid dangling pointer

	// If the variable value is NULL, concatenate only the parts before and after the variable
	if (tmp2 == NULL)
		input = ft_strjoin(tmp1, tmp3); // Join the part before and after the variable
	else
		input = ft_strjoin_con(tmp1, tmp2, tmp3); // Join all three parts (before, value, after)

	// Free the temporary strings to avoid memory leaks
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(key);
	return (input); // Return the new input string with the variable replaced
}

// This function handles the case when a question mark is encountered in the input string.
// It retrieves the current value of g_ext_stats,
// constructs a new string with this value,
// and resets g_ext_stats to 0.
char	*question_handle(char *input, int begin, int *i)
{
	char	*line_new; // New string to hold the modified input
	char	*tmp_1; // Temporary string for the part before the question mark
	char	*tmp_2; // Temporary string for the concatenated result
	char	*nbr_val; // String representation of the exit status
	char	*tail; // Part of the input string after the question mark

	nbr_val = ft_itoa(*exit_status()); // Convert the exit status to a string
	tmp_1 = ft_substr(input, 0, begin); // Get the part before the question mark
	tmp_2 = ft_strjoin(tmp_1, nbr_val); // Concatenate the part before with the exit status
	tail = ft_strdup(&input[*i]); // Get the part of the input after the question mark
	line_new = ft_strjoin(tmp_2, tail); // Concatenate the exit status with the tail
	free(nbr_val); // Free the string representation of the exit status
	free(tmp_1); // Free the temporary string for the part before
	free(tmp_2); // Free the temporary string for the concatenated result
	free(tail); // Free the tail part of the input
	free(input); // Free the original input string
	*exit_status() = 0; // Reset the exit status to 0
	return (line_new); // Return the new input string with the exit status
}

// Check for dollar in the input string and determines if they represent
// an environment variable or a special case ("?"). Updates the iterator
// and calls the appropriate handler function to process the input.
char	*is_dollar(char *input, int *i, t_env *env_dup)
{
	int	begin; // Variable to store the starting position of the dollar sign

	begin = *i; // Set the beginning position to the current index
	if (ft_strchr("?", input[begin + 1])) // Check if the next character is a question mark
	{
		*i += 2; // Move the index past the dollar and the question mark
		return (question_handle(input, begin, i)); // Handle the question mark case
	}
	while (input[++(*i)]) // Loop to find the end of the variable name
	{
		if (!is_valid_char(input[*i])) // Check if the character is not valid
			break; // Exit the loop if an invalid character is found
	}
	if (*i == begin + 1) // If no valid variable name was found
		return (input); // Return the original input string
	input = replace_env_var(input, begin, *i, env_dup); // Replace the environment variable in the input
	return (input); // Return the modified input string
}

