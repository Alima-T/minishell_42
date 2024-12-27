/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:36:13 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 15:06:19 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h" // Includes the header file for the minishell project

/*
Summary of Functions:
1. redir_reading:
This function handles the parsing of input redirection operators (<). It checks for syntax errors, such as if the next character is a newline or another redirection operator. If an error is found, it calls print_msg to report the error and returns a non-zero error code. If valid, it calls finish_check to continue validation.
2. redir_writing:
This function handles the parsing of output redirection operators (>). Similar to redir_reading, it checks for syntax errors related to output redirection. It reports errors using print_msg and returns a non-zero error code for invalid syntax. If valid, it calls finish_check for further validation.
redir_counting:
This function counts the number of redirection operators in the input string and determines whether the redirection is for reading or writing. It calls the appropriate function (redir_reading or redir_writing) based on the type of redirection and checks for errors. It decrements the index to handle specific cases and returns 0 for success or 1 for errors.
This code is part of a parser for a shell-like environment, responsible for validating redirection operators in command-line input. It ensures that the syntax is correct and handles errors appropriately.
*/
/**
 * Handles the reading of redirection operators in the input string.
 * It checks for syntax errors related to input redirection.
 *
 * @param input The input string to be parsed.
 * @param i A pointer to the current index in the input string.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	redir_reading(char *input, int *i)
{
	(*i)++; // Move to the next character after the redirection operator
	// Check for syntax errors: if the next character is a newline or another '>'
	if (input[*i] == '\0' || input[*i] == '>')
		return (print_msg(1, "syntax error - token `newline'", 258)); // Return error for invalid syntax
	// Check for syntax error if the next character is a pipe
	if (input[*i] == '|')
		return (print_msg(1, "syntax error - token `|'", 258)); // Return error for invalid syntax
	// Check for input redirection operator '<'
	if (input[*i] == '<')
	{
		(*i)++; // Move to the next character
		return (finish_check(input, i)); // Call finish_check to validate further
	}
	else
		return (finish_check(input, i)); // Call finish_check for other cases
}

/**
 * Handles the writing of redirection operators in the input string.
 * It checks for syntax errors related to output redirection.
 *
 * @param input The input string to be parsed.
 * @param i A pointer to the current index in the input string.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	redir_writing(char *input, int *i)
{
	(*i)++; // Move to the next character after the redirection operator
	// Check for syntax errors: if the next character is a newline or a pipe
	if (input[*i] == '\0' || input[*i] == '|')
		return (print_msg(1, "syntax error - token `newline'", 258)); // Return error for invalid syntax
	// Check for syntax error if the next character is an input redirection operator '<'
	if (input[*i] == '<')
		return (print_msg(1, "syntax error - token `<'", 258)); // Return error for invalid syntax
	// Check for output redirection operator '>'
	if (input[*i] == '>')
	{
		(*i)++; // Move to the next character
		return (finish_check(input, i)); // Call finish_check to validate further
	}
	else
		return (finish_check(input, i)); // Call finish_check for other cases
}

/**
 * Counts the number of redirection operators in the input string.
 * It determines if the redirection is for reading or writing.
 *
 * @param input The input string to be parsed.
 * @param i A pointer to the current index in the input string.
 * @param redir A character indicating the type of redirection ('<' or '>').
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	redir_counting(char *input, int *i, char redir)
{
	// Check for writing redirection operator '>'
	if (redir == '>' && redir_writing(input, i))
		return (1); // Return 1 if there was an error
	// Check for reading redirection operator '<'
	if (redir == '<' && redir_reading(input, i))
		return (1); // Return 1 if there was an error
	(*i)--; // Decrement the index to handle cases like 'ls >'1'
	return (0); // Return 0 indicating success
}
