/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:33:17 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/04 14:23:55 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//
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
 * Parses special characters in the input string, handling quotes, escape characters,
 * and variable expansions.
 * @param input The original input string to be parsed.
 * @param env_dup A pointer to the environment variables (used for variable expansion).
 * @return The modified input string after processing special characters.
 */
// "", '', $, |, $?, <, >, <<, >>

char	*parse_special_chars(char *input, t_env *env_dup) // "", '', \, $, ;, |, >, >>, <, 'пробел'
{
	int	i;
	// printf("\ninput = %s\n\n", input);
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
			input = is_quote(input, &i);
		if (input[i] == '\\')
			input = is_slash(input, &i);
		if (input[i] == '\"')
			input = is_db_quote(input, &i, env_dup);
		if (input[i] == '$')
			input = is_dollar(input, &i, env_dup);
	}
	// printf("\ninput2 = %s\n\n", input);
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
