/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:04:53 by tbolsako          #+#    #+#             */
/*   Updated: 2025/03/21 17:16:44 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_single_quote(char *input, int *i, bool *in_single_quotes)
{
	*in_single_quotes = !(*in_single_quotes);
	input = is_quote(input, i);
	if (!input[*i])
		return (input);
	if (input[*i] && (input[*i] == '\'' || input[*i] == '\"') && (*i == 0
			|| !is_token_separator(input[*i - 1])))
		return (input);
	*in_single_quotes = false;
	return (input);
}

static char	*handle_double_quote(char *input, int *i, t_env *env_dup)
{
	input = is_db_quote(input, i, env_dup);
	if (!input[*i])
		return (input);
	if (input[*i] && (input[*i] == '\'' || input[*i] == '\"') && (*i == 0
			|| !is_token_separator(input[*i - 1])))
		return (input);
	return (input);
}

static char	*handle_dollar(char *input, int *i, t_env *env_dup)
{
	input = is_dollar(input, i, env_dup);
	return (input);
}

static char	*check_special_char(char *input, int *i, bool *in_single_quotes,
		t_env *env_dup)
{
	if (input[*i] == '\'')
		input = handle_single_quote(input, i, in_single_quotes);
	else if (input[*i] == '\"')
		input = handle_double_quote(input, i, env_dup);
	else if (input[*i] == '$' && !(*in_single_quotes))
	{
		input = handle_dollar(input, i, env_dup);
		if (!input[*i])
			return (input);
		(*i)--;
	}
	return (input);
}

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
		input = check_special_char(input, &i, &in_single_quotes, env_dup);
		if (!input[i])
			break ;
		i++;
	}
	return (input);
}
