/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:47:13 by aokhapki          #+#    #+#             */
/*   Updated: 2025/03/21 17:34:23 by tbolsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*replace_env(char *input, int start, int end, t_env *env_dup)
{
	char	*result;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*key;

	tmp1 = ft_substr(input, 0, start);
	if (input[start + 1] == '{' && input[end - 1] == '}')
		key = ft_substr(input, start + 2, end - start - 3);
	else
		key = ft_substr(input, start + 1, end - start - 1);
	tmp2 = find_in_env(env_dup, key);
	if (tmp2)
		tmp2 = ft_strdup(tmp2);
	else
		tmp2 = ft_strdup("");
	tmp3 = ft_strdup(input + end);
	result = ft_strjoin_con(tmp1, tmp2, tmp3);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(key);
	free(input);
	return (result);
}

static char	*question_handle(char *input, int start, int *i)
{
	char	*line_new;
	char	*tmp_1;
	char	*tmp_2;
	char	*nbr_val;
	char	*tail;

	nbr_val = ft_itoa(*get_exit_status());
	tmp_1 = ft_substr(input, 0, start);
	tmp_2 = ft_strjoin(tmp_1, nbr_val);
	tail = ft_strdup(&input[*i]);
	line_new = ft_strjoin(tmp_2, tail);
	free(nbr_val);
	free(tmp_1);
	free(tmp_2);
	free(tail);
	free(input);
	return (line_new);
}

static char	is_valid_char(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

static char	*handle_curly(char *input, int *i, int start, t_env *env_dup)
{
	int	key_start;
	int	key_end;

	(*i)++;
	while (input[++(*i)])
	{
		if (input[*i] == '}')
		{
			(*i)++;
			break ;
		}
		if (!is_valid_char(input[*i]) && input[*i] != '}')
			return (input);
	}
	if (input[*i - 1] != '}')
		return (input);
	key_start = start + 2;
	key_end = *i - 1;
	if (key_end <= key_start)
		return (input);
	return (replace_env(input, start, *i, env_dup));
}

char	*is_dollar(char *input, int *i, t_env *env_dup)
{
	int	start;

	start = *i;
	if (ft_strchr("?", input[start + 1]))
	{
		*i += 2;
		return (question_handle(input, start, i));
	}
	if (input[start + 1] == '{')
		return (handle_curly(input, i, start, env_dup));
	while (input[++(*i)])
	{
		if (!is_valid_char(input[*i]))
			break ;
	}
	if (*i == start + 1)
		return (input);
	input = replace_env(input, start, *i, env_dup);
	return (input);
}
