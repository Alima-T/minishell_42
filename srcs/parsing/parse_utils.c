/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:33:17 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/19 09:15:10 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*is_slash(char *input, int *i)
{
	char	*tmp_1;
	char	*tmp_2;

	tmp_1 = ft_substr(input, 0, *i);
	tmp_2 = ft_strdup(input + *i + 1);
	free(input);
	input = NULL;
	input = ft_strjoin(tmp_1, tmp_2);
	free(tmp_1);
	free(tmp_2);
	(*i)++;
	return (input);
}

/**
 * Helper function to check if a character is a valid token separator.
 * This helps determine if quoted strings should be treated as
 * separate arguments.
 *
 * @param c The character to check
 * @return true if the character is a separator, false otherwise
 */
static bool	is_token_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

/**
 * Parses special characters in the input string, handling quotes,
 * escape characters,
 * and variable expansions.
 * @param input The original input string to be parsed.
 * @param env_dup A pointer to the environment variables
 * (used for variable expansion).
 * @return The modified input string after processing special characters.
 */
// "", '', $, |, $?, <, >, <<, >>
// "", '', \, $, ;, |, >, >>, <, 'пробел'
char	*parse_special_chars(char *input, t_env *env_dup)
{
	int		i;
	bool	in_single_quotes;

	in_single_quotes = false;
	if (!input || !*input)
		return (input);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			in_single_quotes = !in_single_quotes;
			input = is_quote(input, &i);
			if (!input[i])
				break ;
			if (input[i] && (input[i] == '\'' || input[i] == '\"') && (i == 0
					|| !is_token_separator(input[i - 1])))
				continue ;
			in_single_quotes = false;
		}
		else if (input[i] == '\"')
		{
			input = is_db_quote(input, &i, env_dup);
			if (!input[i])
				break ;
			if (input[i] && (input[i] == '\'' || input[i] == '\"') && (i == 0
					|| !is_token_separator(input[i - 1])))
				continue ;
		}
		// if (input[i] == '$')
		if (input[i] == '$' && !in_single_quotes)
		{
			input = is_dollar(input, &i, env_dup);
			if (!input[i])
				break ;
			continue ;
		}
		i++;
	}
	return (input);
}

// Function to skip over spaces and tabs in an input string
// Returns the index after all consecutive spaces/tabs
int	skip_space_tab(char *inp, int i)
{
	while (inp[i] && (ft_strchr(" ", inp[i]) || ft_strchr("\t", inp[i])))
		i++;
	return (i);
}
