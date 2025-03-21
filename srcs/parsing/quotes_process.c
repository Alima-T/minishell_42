/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:29 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 16:54:13 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static void	free_if_exists(char *ptr)
{
	if (ptr)
		free(ptr);
}

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
		free_if_exists(before);
		free_if_exists(middle);
		free_if_exists(after);
		return (input);
	}
	result = ft_strjoin_con(before, middle, after);
	free(before);
	free(middle);
	free(after);
	free(input);
	return (result);
}
