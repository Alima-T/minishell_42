/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:22:52 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/02 16:44:50 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Summary of Functions:
start_check:
This function checks the beginning of the input string for syntax errors related to command tokens. It verifies if there are any invalid tokens (like |, ;, ||, ;;) at the start of the command and reports errors if found.
2. 
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
		return (print_msg(1, "syntax error - token `||'", 258));
	if (input[i] == '|')
		return (print_msg(1, "syntax error - token `|'", 258));
	if (input[i] == ';' && input[i + 1] == ';')
		return (print_msg(1, "syntax error - token `;;'", 258));
	if (input[i] == ';')
		return (print_msg(1, "syntax error - token `;'", 258));
	return (0);
}

/**
 * Validates the entire input string for syntax errors.
 * It checks for various syntax rules related to commands and redirections.
 * And report error for '\0(new line), |, >, <, ;
 * @param input The input string to be validated.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	validator(char *input)
{
	int	i; // Index variable for traversing the input string

	if (!input) // Check if the input is NULL
		return (1); // Return 1 indicating an error
	i = skip_space_tab(input, 0);
	// Check for invalid tokens at the start
	if (input[i] == '|' || input[i] == ';')
		return (start_check(input, i));
	while (input[i])
	{
		if ((input[i] == '|' || input[i] == ';') && count_pipe_delim(input, i + 1))
			return (1);
		if (input[i] == '\'' && count_quote(input, &i, input[i]))
			return (1); 
		if (input[i] == '\"' && count_quote(input, &i, input[i]))
			return (1);
		if ((input[i] == '<' || input[i] == '>') && redir_counting(input, &i, input[i]))
			return (1);
		i++;
	}
	return (0);
}