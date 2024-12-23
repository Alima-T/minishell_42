/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:47:13 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/23 15:36:21 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// check if a character is a valid key character (underscore or alphanumeric).
char	is_valid_char(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1); // valid
	return (0);     // false
}

// Replaces an environment variable in the input string with its corresponding value.
// It extracts the key from the input, retrieves its value from the environment,
// and constructs a new string with the substituted value.
char	*replace_env_var(char *input, int start, int end, t_env *env_dup)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*key;
	// Extract the environment variable key from the input string.
	// The key starts after the '$' symbol and ends at the position of 'end'.
	// We take a substring from 'begin + 1' to 'end - begin - 1' to get the key.
	tmp1 = ft_substr(input, 0, start);
	key = ft_substr(input, start + 1, end - start - 1);
	tmp2 = ft_strdup(find_in_env(env_dup, key));
	tmp3 = ft_strdup(input + end);
	free(input);
	input = NULL;
	if (tmp2 == NULL)
		input = ft_strjoin(tmp1, tmp3);
	else
		input = ft_strjoin_con(tmp1, tmp2, tmp3);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(key);
	return (input);
}

// This function handles the case when a question mark is encountered in the input string.
// It retrieves the current value of g_ext_stats,
//	constructs a new string with this value,
// and resets g_ext_stats to 0.
char	*question_handle(char *input, int begin, int *i)
{
	char	*line_new;
	char	*tmp_1;
	char	*tmp_2;
	char	*nbr_val;
	char	*tail;

	nbr_val = ft_itoa(*exit_status());
	tmp_1 = ft_substr(input, 0, begin);
	tmp_2 = ft_strjoin(tmp_1, nbr_val);
	tail = ft_strdup(&input[*i]);
	line_new = ft_strjoin(tmp_2, tail);
	free(nbr_val);
	free(tmp_1);
	free(tmp_2);
	free(tail);
	free(input);
	*exit_status() = 0;
	return (line_new);
}

// check for dollar in the input string and determines if they represent
// an environment variable or a special case ("?"). iupdates the iterator
// and calls the appropriate handler function to process the input.
char	*is_dollar(char *input, int *i, t_env *env_dup)
{
	int	begin;

	begin = *i;
	if (ft_strchr("?", input[begin + 1]))
	{
		*i += 2;
		return (question_handle(input, begin, i));
	}
	while (input[++(*i)])
	{
		if (!is_valid_char(input[*i]))
			break ;
	}
	if (*i == begin + 1)
		return (input);
	input = replace_env_var(input, begin, *i, env_dup);
	return (input);
}
