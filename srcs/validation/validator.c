/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:22:52 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 15:11:20 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Summary of Functions:
start_check:
This function checks the beginning of the input string for syntax errors related to command tokens. It verifies if there are any invalid tokens (like |, ;, ||, ;;) at the start of the command and reports errors if found.
2. finish_check:
This function checks the end of the input string for syntax errors. It verifies if the end of the input is reached or if there are invalid tokens (like |, >, <, ;) at the end of the command. It reports errors if any are found.
3. count_pipe_delim:
This function counts the number of pipe delimiters in the input string and checks for syntax errors related to their usage. It checks for single and double pipes (|, ||) and single and double semicolons (;, ;;), reporting errors as necessary.
count_quote:
This function counts the number of quotes in the input string and checks for unclosed quotes. It reports a syntax error if it finds an unclosed quote.
5. validator:
This function validates the entire input string for syntax errors. It checks for invalid tokens at the start and end, validates pipes, quotes, and redirection operators throughout the input, and returns an error code if any issues are found.
This code is part of a parser for a shell-like environment, responsible for validating command-line input for syntax errors related to commands and redirections. It ensures that the input adheres to the expected syntax rules and reports errors appropriately.*/

/**
 * Checks the start of the input for syntax errors related to command tokens.
 * It verifies if there are any invalid tokens at the beginning of the command.
 *
 * @param input The input string to be validated.
 * @param i The current index in the input string.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	start_check(char *input, int i)
{
	// Check for double pipe '||' at the start
	if (input[i] == '|' && input[i + 1] == '|')
		return (print_msg(1, "syntax error - token `||'", 258)); // Report error for '||'
	// Check for single pipe '|' at the start
	if (input[i] == '|')
		return (print_msg(1, "syntax error - token `|'", 258)); // Report error for '|'
	// Check for double semicolon ';;' at the start
	if (input[i] == ';' && input[i + 1] == ';')
		return (print_msg(1, "syntax error - token `;;'", 258)); // Report error for ';;'
	// Check for single semicolon ';' at the start
	if (input[i] == ';')
		return (print_msg(1, "syntax error - token `;'", 258)); // Report error for ';'
	return (0); // Return 0 indicating no errors
}

/**
 * Checks the end of the input for syntax errors related to command tokens.
 * It verifies if there are any invalid tokens at the end of the command.
 *
 * @param input The input string to be validated.
 * @param i A pointer to the current index in the input string.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
 
int	finish_check(char *input, int *i)
{
	*i = skip_space_tab(input, *i); // Skip any leading whitespace
	// Check if the end of the input is reached
	if (input[*i] == '\0')
		return (print_msg(1, "syntax error - token `newline'", 258)); // Report error for newline
	// Check for single pipe '|' at the end
	if (input[*i] == '|')
		return (print_msg(1, "syntax error - token `|'", 258)); // Report error for '|'
	// Check for output redirection '>' at the end
	if (input[*i] == '>')
		return (print_msg(1, "syntax error - token `>'", 258)); // Report error for '>'
	// Check for input redirection '<' at the end
	if (input[*i] == '<')
		return (print_msg(1, "syntax error - token `<'", 258)); // Report error for '<'
	// Check for single semicolon ';' at the end
	if (input[*i] == ';')
		return (print_msg(1, "syntax error - token `;'", 258)); // Report error for ';'
	return (0); // Return 0 indicating no errors
}

/**
 * Counts the number of pipe delimiters in the input string.
 * It checks for syntax errors related to pipe usage.
 *
 * @param input The input string to be validated.
 * @param i The current index in the input string.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	count_pipe_delim(char *input, int i)
{
	i = skip_space_tab(input, i); // Skip any leading whitespace
	// Check for single pipe '|' at the current position
	if (input[i] == '|')
	{
		// Check for double pipe '||' at the next position
		if (input[i + 1] == '|')
			return (print_msg(1, "syntax error token `||'", 258)); // Report error for '||'
		return (print_msg(1, "syntax error token `|'", 258)); // Report error for '|'
	}
	// Check for single semicolon ';' at the current position
	if (input[i] == ';')
	{
		// Check for double semicolon ';;' at the next position or previous position
		if (input[i + 1] == ';' || input[i - 1] == ';')
			return (print_msg(1, "syntax error token `;;'", 258)); // Report error for ';;'
		return (print_msg(1, "syntax error token `;'", 258)); // Report error for ';'
	}
	return (0); // Return 0 indicating no errors
}

/**
 * Counts the number of quotes in the input string.
 * It checks for unclosed quotes and reports a syntax error if found.
 *
 * @param input The input string to be validated.
 * @param i A pointer to the current index in the input string.
 * @param quote The type of quote being checked (single or double).
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	count_quote(char *input, int *i, char quote)
{
	// Loop through the input string to find the closing quote
	while (input[++(*i)])
	{
		if (input[*i] == quote) // Check for the closing quote
			return (0); // Return 0 if the closing quote is found
	}
	return (print_msg(1, "syntax error with unclosed quotes", 258)); // Report error for unclosed quotes
}

/**
 * Validates the entire input string for syntax errors.
 * It checks for various syntax rules related to commands and redirections.
 *
 * @param input The input string to be validated.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	validator(char *input)
{
	int	i; // Index variable for traversing the input string

	if (!input) // Check if the input is NULL
		return (1); // Return 1 indicating an error
	i = skip_space_tab(input, 0); // Skip leading whitespace
	// Check for invalid tokens at the start
	if (input[i] == '|' || input[i] == ';')
		return (start_check(input, i)); // Validate the start of the input
	// Loop through the input string to validate each part
	while (input[i])
	{
		// Check for pipes and validate them
		if ((input[i] == '|' || input[i] == ';') && count_pipe_delim(input, i + 1))
			return (1); // Return 1 if there was an error
		// Check for single quotes and validate them
		if (input[i] == '\'' && count_quote(input, &i, input[i]))
			return (1); // Return 1 if there was an error
		// Check for double quotes and validate them
		if (input[i] == '\"' && count_quote(input, &i, input[i]))
			return (1); // Return 1 if there was an error
		// Check for redirection operators and validate them
		if ((input[i] == '<' || input[i] == '>') && redir_counting(input, &i, input[i]))
			return (1); // Return 1 if there was an error
		i++; // Move to the next character
	}
	return (0); // Return 0 indicating no errors
}
