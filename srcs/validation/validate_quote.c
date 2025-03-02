/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:15:14 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/02 16:38:31 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h" 

/**
 * Counts the number of pipe delimiters in the input string.
 * It checks for syntax errors related to pipe usage.
 *Report error for ||, |, ;;
 * @param input The input string to be validated.
 * @param i The current index in the input string.
 * @return An integer indicating success (0) or an error code (non-zero).
 */
int	count_pipe_delim(char *input, int i)
{
	i = skip_space_tab(input, i);
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			return (print_msg(1, "syntax error token `||'", 258));
		return (print_msg(1, "syntax error token `|'", 258));
	}
	if (input[i] == ';')
	{
		if (input[i + 1] == ';' || input[i - 1] == ';')
			return (print_msg(1, "syntax error token `;;'", 258));
		return (print_msg(1, "syntax error token `;'", 258));
	}
	return (0);
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
	while (input[++(*i)])
	{
		if (input[*i] == quote) // Check for the closing quote
			return (0);
	}
	return (print_msg(1, "syntax error - unclosed quotes", 258)); // Report error for unclosed quotes
}