/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/17 20:27:17 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * function processes single quotes in the input. It finds the position
 * of the closing single quote and calls combine_subs to handle the substring
 * between the opening and closing quotes.
 *
 * @param input The original input string.
 * @param i A pointer to the current index in the input string.
 * @return The modified input string after processing single quotes.
 */
char	*is_quote(char *input, int *i)
{
	int	start;

	// Store the starting index of the quote.
	start = *i;
	// Increment the index until a closing quote is found.
	while (input[++(*i)])
	{
		// Check for the closing single quote.
		if (input[*i] == '\'')
			break ;
	}
	// Call combine_subs to process the substring.
	input = combine_subs(input, start, *i);
	// modified input string.
	return (input);
}

/**
 * function processes double quotes in the input string. It handles dollar signs
 * within the quotes, updating the iterator as it finds these characters.
 * It calls
	* combine_subs to handle the substring between the opening and closing double quotes.
 * @param input The original input string.
 * @param i A pointer to the current index in the input string.

	* @param env_dup A pointer to the environment variables (used for variable expansion).
 * @return The modified input string after processing double quotes.
 */
char	*is_db_quote(char *input, int *i, t_env *env_dup)
{
	int	start;

	start = *i; // Store the starting index of the double quote.
	while (input[++(*i)])
	// Increment the index until a closing double quote is found.
	{
		/* в двойных кавычках отрабатывает \, если после него идет ", $ или \ */
		if (input[*i] == '\\' && (input[*i + 1] == '\"' || input[*i + 1] == '$'
				|| input[*i + 1] == '\\'))
			input = is_slash(input, i);
		if (input[*i] == '$')
			// Check for dollar sign for variable substitution.
			input = is_dollar(input, i, env_dup);
		if (input[*i] == '\"') // Check for the closing double quote.
			break ;
	}
	input = combine_subs(input, start, *i);
	// Call combine_subs to process the substring.
	return (input); // Return the modified input string.
}

/**

	* function processes a substring of the input string by extracting parts before,
 * between,
	 and after specified indices (start and end). It frees the original input
 * and returns a new str that combines the extracted parts.
 * @param input The original input string.
 * @param start The starting index of the substring to be processed.
 * @param end The ending index of the substring to be processed.
 * @return The combined string after processing.
 */
char	*combine_subs(char *input, int start, int end)
{
	char *before; // part before the quotes
	char *middle; // part inside the quotes
	char *after;  // part after the quotes
	char *result; // final result
	// make sure we have valid indices
	if (!input || start < 0 || end < start || end >= (int)ft_strlen(input))
	{
		// return the original string in case of invalid input
		return (input);
	}
	// extract the parts
	// Part before the start index
	before = ft_substr(input, 0, start);
	// Part between start and end
	middle = ft_substr(input, start + 1, end - start - 1);
	// Part after the end index
	after = ft_strdup(input + end + 1);
	// check for allocation failures
	if (!before || !middle || !after)
	{
		// free any alloccated memory and return the original to avoid leaks
		if (before)
			free(before);
		if (middle)
			free(middle);
		if (after)
			free(after);
		return (input);
	}
	// Combine the three parts into a new string
	result = ft_strjoin_con(before, middle, after);
	// free the temporary strings
	free(before);
	free(middle);
	free(after);
	// Free the original input string to avoid memory leaks.
	free(input);
	// Return the newly combined string
	return (result);
}
