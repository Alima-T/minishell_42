/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_special_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:21:52 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 14:08:09 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Parses special characters in the input string, handling quotes, escape characters,
 * and variable expansions.
 * 
 * @param input The original input string to be parsed.
 * @param env_dup A pointer to the environment variables (used for variable expansion).
 * @return The modified input string after processing special characters.
 */
// "", '', $, |, $?, <, >, <<, >>

char	*parse_special_chars(char *input, t_env *env_dup)
{
	int i;
	i = 0;
	while(input[i])
	{
		if(input[i] == '\'')
			input = is_quote(input, &i);
		if(input[i] == '\"')
			input = is_double_quote(input, &i, env_dup);
		if(input[i] == '$')
			input = is_dollar(input, &i, env_dup);
		i++;
	}
	return (input);
}
