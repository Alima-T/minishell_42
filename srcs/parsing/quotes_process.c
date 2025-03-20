/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/20 13:12:55 by tbolsako         ###   ########.fr       */
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

	start = *i;
	while (input[++(*i)])
	{
		if (input[*i] == '\'')
			break ;
	}
	input = combine_subs(input, start, *i);
	return (input);
}

/**
 * function processes double quotes in the input string. It handles dollar signs
 * within the quotes, updating the iterator as it finds these characters.
 * It calls
 * combine_subs to handle the substring between the opening and closing double
 * quotes.
 * @param input The original input string.
 * @param i A pointer to the current index in the input string.
 * @param env_dup A pointer to the environment variables (used for variable
 * expansion).
 * @return The modified input string after processing double quotes.
 */
char	*is_db_quote(char *input, int *i, t_env *env_dup)
{
	int	start;

	start = *i;
	while (input[++(*i)])
	{
		if (input[*i] == '\\' && (input[*i + 1] == '\"' || input[*i + 1] == '$'
				|| input[*i + 1] == '\\'))
			input = is_slash(input, i);
		if (input[*i] == '$')
			input = is_dollar(input, i, env_dup);
		if (input[*i] == '\"')
			break ;
	}
	input = combine_subs(input, start, *i);
	return (input);
}

/**
 * function processes a substring of the input string by extracting parts before,
 * between, and after specified indices (start and end). It frees the original
 * input and returns a new str that combines the extracted parts.
 * @param input The original input string.
 * @param start The starting index of the substring to be processed.
 * @param end The ending index of the substring to be processed.
 * @return The combined string after processing.
 */
char	*combine_subs(char *input, int start, int end)
{
	char	*before;
	char	*middle;
	char	*after;
	char	*result;

	if (!input || start < 0 || end < start || end >= (int)ft_strlen(input))
		return (input);
	before = ft_substr(input, 0, start);
	middle = ft_substr(input, start + 1, end - start - 1);
	after = ft_strdup(input + end + 1);
	if (!before || !middle || !after)
	{
		if (before)
			free(before);
		if (middle)
			free(middle);
		if (after)
			free(after);
		return (input);
	}
	result = ft_strjoin_con(before, middle, after);
	free(before);
	free(middle);
	free(after);
	free(input);
	return (result);
}
