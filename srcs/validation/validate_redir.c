/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:36:13 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/17 19:28:50 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Summary of Functions:
1. finish_check:
This function checks the end of the input string for syntax errors. It verifies if the end of the input is reached or if there are invalid tokens (like |, >, <, ;) at the end of the command. It reports errors if any are found.
2. redir_reading:
This function handles the parsing of input redirection operators (<). It checks for syntax errors, such as if the next character is a newline or another redirection operator. If an error is found, it calls print_msg to report the error and returns a non-zero error code. If valid, it calls finish_check to continue validation.
3. redir_writing:
This function handles the parsing of output redirection operators (>). Similar to redir_reading, it checks for syntax errors related to output redirection. It reports errors using print_msg and returns a non-zero error code for invalid syntax. If valid, it calls finish_check for further validation.
4. redir_counting:
This function counts the number of redirection operators in the input string and determines whether the redirection is for reading or writing. It calls the appropriate function (redir_reading or redir_writing) based on the type of redirection and checks for errors. It decrements the index to handle specific cases and returns 0 for success or 1 for errors.
This code is part of a parser for a shell-like environment, responsible for validating redirection operators in command-line input. It ensures that the syntax is correct and handles errors appropriately.
*/
/**
 * Checks the end of the input for syntax errors related to command tokens 
 * and report error for '\0(new line), |, >, <, ;
 * @param input The input string to be validated.
 * @param i A pointer to the current index in the input string.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	finish_check(char *input, int *i)
{
	*i = skip_space_tab(input, *i); // Skip any leading whitespace
	// Check if the end of the input is reached
	if (input[*i] == '\0')
		return (print_msg(1, "syntax error - token `newline'", 258));
	if (input[*i] == '|')
		return (print_msg(1, "syntax error - token `|'", 258));
	if (input[*i] == '>')
		return (print_msg(1, "syntax error - token `>'", 258));
	if (input[*i] == '<')
		return (print_msg(1, "syntax error - token `<'", 258));
	if (input[*i] == ';')
		return (print_msg(1, "syntax error - token `;'", 258));
	return (0);
}

/**
 * Handles the writing of redirection operators in the input string. 
 * And report for invalid syntax \0(new line), |, >, <
 * @param input The input string to be parsed.
 * @param i A pointer to the current index in the input string.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	redir_writing(char *input, int *i)
{
	(*i)++;
	if (input[*i] == '\0' || input[*i] == '|')
		return (print_msg(1, "syntax error - token `newline'", 258));
	if (input[*i] == '<')
		return (print_msg(1, "syntax error - token `<'", 258));
	if (input[*i] == '>')
	{
		(*i)++;
		return (finish_check(input, i));
	}
	else
		return (finish_check(input, i));
}

/**
 * Handles the reading of redirection operators in the input string.
 * And report for invalid syntax \0(new line), |, >, <
 * @param input The input string to be parsed.
 * @param i A pointer to the current index in the input string.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	redir_reading(char *input, int *i)
{
	// Move to the next character after the redirection operator
	(*i)++;
	// Check for syntax errors: if the next character is a newline or another '>'
	if (input[*i] == '\0' || input[*i] == '>')
		return (print_msg(1, "syntax error - token `newline'", 258));
	if (input[*i] == '|')
		return (print_msg(1, "syntax error - token `|'", 258));
	if (input[*i] == '<')
	{
		(*i)++;
		return (finish_check(input, i));
	}
	else
		return (finish_check(input, i));
}

/**
 * Counts the number of redirection operators in the input string.
 * It determines if the redirection is for reading or writing.
 * @param input The input string to be parsed.
 * @param i A pointer to the current index in the input string.
 * @param redir A character indicating the type of redirection ('<' or '>').
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	redir_counting(char *input, int *i, char redir)
{
	if (redir == '>' && redir_writing(input, i))
		return (1);
	if (redir == '<' && redir_reading(input, i))
		return (1);
	// Decrement the index to handle cases like 'ls >'1'
	(*i)--;
	return (0);
}
